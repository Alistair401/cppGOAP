cmake_minimum_required(VERSION 3.20)

project(cppGOAP)

set (TARGET_NAME ${PROJECT_NAME})

include_directories("include")

set(INCLUDE_FILES
		"include/Action.h"
		"include/DistanceFunctionMap.h"
		"include/Effect.h"
		"include/EvaluatedAction.h"
		"include/Hash.h"
		"include/Node.h"
		"include/NodeVector.h"
		"include/OpenSet.h"
		"include/Planner.h"
		"include/Precondition.h"
		"include/SimpleAction.h"
		"include/SimpleEffect.h"
		"include/SimplePrecondition.h"
		"include/SlicedPlan.h"
		"include/Value.h"
		"include/WorldState.h"
		"include/WorldStateKey.h")

set(SRC_FILES 
        "src/Node.cpp"
        "src/NodeVector.cpp"
        "src/OpenSet.cpp"
        "src/Planner.cpp"
        "src/SimpleAction.cpp"
        "src/SimpleEffect.cpp"
        "src/SimplePrecondition.cpp"
        "src/SlicedPlan.cpp"
        "src/Value.cpp"
        "src/WorldState.cpp"
        "src/WorldStateKey.cpp"
        "src/Action.cpp"
        "src/DistanceFunctionMap.cpp")

add_library(${TARGET_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)