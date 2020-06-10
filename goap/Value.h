#pragma once
#include <vector>
#include <memory>

namespace goap
{
    class TypedData;

    enum class Type 
    {
        EMPTY,
        BOOL,
        FLOAT,
        INT,
        VECTOR
    };

    class Value
    {
    public:
        Value();
        Value(const Value& other);
        Value& operator=(const Value& other);

        Value(bool value);
        Value(int value);
        Value(float value);

        Value(const std::vector<Value>& values);
        Value(std::vector<Value>&& values);

        Type GetType() const;

        bool AsBool() const;
        float AsFloat() const;
        int AsInt() const;

        bool operator==(const Value& other) const;

        Value operator|(const Value& other) const;
        Value operator~() const;
        Value operator&(const Value& other) const;

    private:
        std::shared_ptr<TypedData> data;
    };

    class TypedData 
    {
    public:

        virtual Type GetType() const = 0;
        virtual TypedData* Clone() const = 0;
        virtual bool operator==(const TypedData& other) const = 0;

        virtual bool AsBool() const;
        virtual float AsFloat() const;
        virtual int AsInt() const;
        virtual const std::vector<Value> AsVector() const;

        virtual TypedData* operator|(const TypedData& other) const;
        virtual TypedData* operator~() const;
        virtual TypedData* operator&(const TypedData& other) const;
    };
}
