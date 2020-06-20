#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include "Planner.h"

#define WIN32

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

enum class CellData 
{
    EMPTY,
    WALL,
    AGENT,
    GOAL
};

struct Tool 
{
    CellData cell;
    std::string name;
};

enum ActionId
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum VariableId
{
    POS_X,
    POS_Y,
    WALKABLE
};

std::int64_t AgentId = std::numeric_limits<std::int64_t>::max();

std::int64_t ElegantPair(int x, int y)
{
    return (x >= y) ? (x * x + x + y) : (y * y + x);
}

ActionId OppositeAction(ActionId a)
{
    switch (a)
    {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    default:
        return NONE;
    }
}

int gridSize = 10;
int cellSize = 36; 

class MoveAction : public goap::Action
{
public:
    MoveAction(int id, int x, int y)
        : goap::Action(id, 1)
        , x(x)
        , y(y)
    {
    }

    virtual bool ResolvesAny(const goap::WorldState& start, const goap::WorldState& ws) const override
    {
        // Prune this search if there are unresolvable walkable cells
        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                if (ws.Get(WALKABLE, (void*)ElegantPair(x, y)) != nullptr)
                {
                    return false;
                }
            }
        }

        const goap::Value* maybeX = ws.Get(POS_X, (void*)AgentId);
        const goap::Value* maybeY = ws.Get(POS_Y, (void*)AgentId);
        
        int agentX = maybeX == nullptr ? start.Get(POS_X, (void*)AgentId)->AsInt() : maybeX->AsInt();
        int agentY = maybeY == nullptr ? start.Get(POS_Y, (void*)AgentId)->AsInt() : maybeY->AsInt();

        int sourceX = agentX + (this->x * -1);
        int sourceY = agentY + (this->y * -1);

        return 0 <= sourceX && sourceX < gridSize
            && 0 <= sourceY && sourceY < gridSize
            && 0 <= agentX && agentX < gridSize
            && 0 <= agentY && agentY < gridSize;
    }

    virtual goap::PlannedAction Resolve(const goap::WorldState& start, goap::WorldState& ws) const override
    {
        const goap::Value* maybeX = ws.Get(POS_X, (void*)AgentId);
        const goap::Value* maybeY = ws.Get(POS_Y, (void*)AgentId);

        int agentX = maybeX == nullptr ? start.Get(POS_X, (void*)AgentId)->AsInt() : maybeX->AsInt();
        int agentY = maybeY == nullptr ? start.Get(POS_Y, (void*)AgentId)->AsInt() : maybeY->AsInt();

        int sourceX = agentX + (this->x * -1);
        int sourceY = agentY + (this->y * -1);

        ws.Set(POS_X, (void*)AgentId, sourceX);
        ws.Set(POS_Y, (void*)AgentId, sourceY);

        ws.Set(WALKABLE, (void*)ElegantPair(agentX, agentY), true);

        return goap::PlannedAction(this->id_);
    }

private:
    int x;
    int y;
};

int main(int argc, char** argv)
{
    SDL_Color gridBackgroundColour = { 22, 22, 22, 255 };
    SDL_Color gridLineColour = { 44, 44, 44, 255 };
    SDL_Color wallColour = { 171, 183, 183, 255 };
    SDL_Color agentColour = { 145, 88, 173, 255 };
    SDL_Color goalColour = { 38, 166, 91, 255 };

    std::vector<Tool> tools = 
    { 
        Tool{ CellData::EMPTY, "Clear" },
        Tool{ CellData::WALL , "Wall"  },
        Tool{ CellData::AGENT, "Agent" },
        Tool{ CellData::GOAL , "Goal"  }
    };

    std::vector<std::vector<CellData>> gridData(gridSize, std::vector<CellData>(gridSize, CellData::EMPTY));

    int windowWidth = (gridSize * cellSize) + 1;
    int windowHeight = (gridSize * cellSize) + 1;

    float tickTime = 500.0;

    bool mousePressed = false;
    SDL_Point cursor{};
    size_t toolIndex = 0;
    std::vector<goap::PlannedAction> plan;
    
    std::vector<std::shared_ptr<goap::Action>> actions;
    actions.emplace_back(new MoveAction(UP, 0, -1));
    actions.emplace_back(new MoveAction(DOWN, 0, 1));
    actions.emplace_back(new MoveAction(LEFT, -1, 0));
    actions.emplace_back(new MoveAction(RIGHT, 1, 0));

    goap::DistanceFunction manhattanDistance = [](const goap::Value& a, const goap::Value* b)
    {
        if (b == nullptr)
        {
            return a.AsInt();
        }
        else
        {
            return std::abs(a.AsInt() - b->AsInt());
        }
    };

    goap::DistanceFunctionMap distanceFunctions;
    distanceFunctions.Set(POS_X, manhattanDistance);
    distanceFunctions.Set(POS_Y, manhattanDistance);

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;

    SDL_SetMainReady();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer);

    auto lastTick = std::chrono::system_clock::now();

    SDL_bool done = SDL_FALSE;
    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;
            case SDL_MOUSEMOTION:
                cursor.x = event.motion.x;
                cursor.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePressed = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mousePressed = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_SLASH:
                    toolIndex = (toolIndex + 1) % tools.size();
                }
            }
        }

        if (mousePressed)
        {
            int cellX = cursor.x / cellSize;
            int cellY = cursor.y / cellSize;

            const Tool& t = tools[toolIndex];
            if (t.cell == CellData::AGENT || t.cell == CellData::GOAL) 
            {
                for (int x = 0; x < gridSize; x++)
                {
                    for (int y = 0; y < gridSize; y++)
                    {
                        if (gridData[y][x] == t.cell)
                        {
                            gridData[y][x] = CellData::EMPTY;
                        }
                    }
                }
            }

            gridData[cellY][cellX] = tools[toolIndex].cell;
        }

        if (plan.empty()) 
        {
            bool foundGoal = false;
            bool foundAgent = false;
            SDL_Point goalCell{};
            SDL_Point agentCell{};

            goap::WorldState start;

            for (int x = 0; x < gridSize; x++)
            {
                for (int y = 0; y < gridSize; y++) 
                {
                    CellData cell = gridData[y][x];

                    if (cell == CellData::GOAL)
                    {
                        foundGoal = true;
                        goalCell.x = x;
                        goalCell.y = y;
                    }

                    if (cell == CellData::AGENT)
                    {
                        foundAgent = true;
                        agentCell.x = x;
                        agentCell.y = y;
                    }

                    start.Set(WALKABLE, (void*)ElegantPair(x, y), cell != CellData::WALL);
                }
            }

            if (foundGoal && foundAgent)
            {
                start.Set(POS_X, (void*)AgentId, agentCell.x);
                start.Set(POS_Y, (void*)AgentId, agentCell.y);

                goap::WorldState goal;
                goal.Set(POS_X, (void*)AgentId, goalCell.x);
                goal.Set(POS_Y, (void*)AgentId, goalCell.y);
                
                plan = goap::Planner::Plan(start, goal, actions, distanceFunctions);
                std::reverse(plan.begin(), plan.end());
            }
        }

        auto now = std::chrono::system_clock::now();
        long long duration = (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick)).count();
        if (duration >= tickTime)
        {
            lastTick = now;

            if (!plan.empty())
            {
                goap::PlannedAction a = plan.back();
                
                SDL_Point agentCell{};
                for (int x = 0; x < gridSize; x++) 
                {
                    for (int y = 0; y < gridSize; y++) 
                    {
                        if (gridData[y][x] == CellData::AGENT) 
                        {
                            agentCell.x = x;
                            agentCell.y = y;
                            gridData[y][x] = CellData::EMPTY;
                        }
                    }
                }

                int newX = agentCell.x;
                int newY = agentCell.y;
                switch (a.GetId())
                {
                case UP:
                    newY--;
                    break;
                case DOWN:
                    newY++;
                    break;
                case LEFT:
                    newX--;
                    break;
                case RIGHT:
                    newX++;
                    break;
                }
                gridData[newY][newX] = CellData::AGENT;
                
                plan.pop_back();
            }
        }

        SDL_SetWindowTitle(window, tools[toolIndex].name.c_str());

        SDL_SetRenderDrawColor(renderer, gridBackgroundColour.r, gridBackgroundColour.g, gridBackgroundColour.b, gridBackgroundColour.a);
        SDL_RenderClear(renderer);

        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                CellData cell = gridData[y][x];

                switch (cell) 
                {
                case CellData::EMPTY:
                    continue;
                case CellData::WALL:
                    SDL_SetRenderDrawColor(renderer, wallColour.r, wallColour.g, wallColour.b, wallColour.a);
                    break;
                case CellData::AGENT:
                    SDL_SetRenderDrawColor(renderer, agentColour.r, agentColour.g, agentColour.b, agentColour.a);
                    break;
                case CellData::GOAL:
                    SDL_SetRenderDrawColor(renderer, goalColour.r, goalColour.g, goalColour.b, goalColour.a);
                    break;
                }

                SDL_Rect cellRect =
                {
                    x * cellSize,
                    y * cellSize,
                    cellSize,
                    cellSize,
                };

                SDL_RenderFillRect(renderer, &cellRect);
            }
        }

        SDL_SetRenderDrawColor(renderer, gridLineColour.r, gridLineColour.g, gridLineColour.b, gridLineColour.a);

        for (int x = 0; x < 1 + gridSize * cellSize; x += cellSize)
        {
            SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
        }

        for (int y = 0; y < 1 + gridSize * cellSize; y += cellSize)
        {
            SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}