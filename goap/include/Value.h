#pragma once
#include <variant>

namespace goap
{
    enum class Type : size_t
    {
        EMPTY,
        BOOL,
        INT
    };

    class Value
    {
    public:
        Value();

        Value(bool value);
        Value(int value);

        Type GetType() const;

        bool AsBool() const;
        int AsInt() const;

        std::size_t GetHashCode() const;

        bool operator==(const Value& other) const;
        bool operator!=(const Value& other) const;
    private:
        std::variant<std::monostate, bool, int> data;
    };
}
namespace std
{
    template <>
    struct hash<goap::Value>
    {
        std::size_t operator()(const goap::Value& v) const
        {
            return v.GetHashCode();
        }
    };
}
