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

goap::Value::Value(float value)
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

float goap::Value::AsFloat() const
{
    return std::get<float>(this->data);
}

int goap::Value::AsInt() const
{
    return std::get<int>(this->data);
}

bool goap::Value::operator==(const Value& other) const
{
    return this->data == other.data;
}

bool goap::Value::operator!=(const Value& other) const
{
    return this->data != other.data;
}
