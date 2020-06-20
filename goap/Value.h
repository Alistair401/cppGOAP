#pragma once
#include <variant>

namespace goap
{
    enum class Type : size_t
    {
        EMPTY,
        BOOL,
        FLOAT,
        INT
    };

    class Value
    {
    public:
        Value();

        Value(bool value);
        Value(int value);
        Value(float value);

        Type GetType() const;

        bool AsBool() const;
        float AsFloat() const;
        int AsInt() const;

        bool operator==(const Value& other) const;
        bool operator!=(const Value& other) const;
    private:
        std::variant<std::monostate, bool, float, int> data;
    };
}