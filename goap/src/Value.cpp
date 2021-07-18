#include "Value.h"

goap::Value::Value()
{
}

goap::Value::Value(bool value)
    : data(value)
{
}

goap::Value::Value(int value)
    : data(value)
{
}

goap::Type goap::Value::GetType() const
{
    return static_cast<Type>(this->data.index());
}

bool goap::Value::AsBool() const
{
    return std::get<bool>(this->data);
}

int goap::Value::AsInt() const
{
    return std::get<int>(this->data);
}

std::size_t goap::Value::GetHashCode() const
{
    return std::hash<std::variant<std::monostate, bool, int>>{}(this->data);
}

bool goap::Value::operator==(const Value& other) const
{
    return this->data == other.data;
}

bool goap::Value::operator!=(const Value& other) const
{
    return this->data != other.data;
}
