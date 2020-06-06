#include "Value.h"

namespace goap 
{
	class EmptyData : public TypedData 
	{
		virtual Type GetType() const override
		{
			return Type::EMPTY;
		}

		virtual TypedData* Clone() const override
		{
			return new EmptyData;
		}

		// Inherited via TypedData
		virtual bool operator==(const TypedData& other) const override
		{
			return other.GetType() == Type::EMPTY;
		}
	};

	template <Type type, typename T>
	class Data : public TypedData
	{
	public:
		Data(const T& value)
			: value(value)
		{
		}

		Data(T&& value)
			: value(std::move(value))
		{
		}

		virtual Type GetType() const override
		{
			return type;
		}
	protected:
		const T value;
	};

	class BoolData : public Data<Type::BOOL, bool>
	{
	public:
		BoolData(bool value)
			: Data(value)
		{
		}

		virtual bool AsBool() const override
		{
			return this->value;
		}

		virtual TypedData* Clone() const override
		{
			return new BoolData(this->value);
		}

		virtual bool operator==(const TypedData& other) const override
		{
			return other.GetType() == Type::BOOL && this->value == other.AsBool();
		}

		virtual TypedData* operator|(const TypedData& other) const override
        {
			if (other.GetType() == Type::BOOL)
			{
                return new BoolData(this->value | other.AsBool());
            }
            else
			{
                return nullptr;
            }
        }
	};

	class FloatData : public Data<Type::FLOAT, float>
	{
	public:
		FloatData(float value)
			: Data(value)
		{
		}

		virtual float AsFloat() const override
		{
			return this->value;
		}

		virtual TypedData* Clone() const override
		{
			return new FloatData(this->value);
		}

        virtual bool operator==(const TypedData& other) const override
        {
            return other.GetType() == Type::FLOAT && this->value == other.AsFloat();
        }
    };

	class IntData : public Data<Type::INT, int>
	{
	public:
		IntData(int value)
			: Data(value)
		{
		}

		virtual int AsInt() const override
		{
			return this->value;
		}

		virtual TypedData* Clone() const override
		{
			return new IntData(this->value);
		}

		virtual bool operator==(const TypedData& other) const override
		{
			return other.GetType() == Type::INT && this->value == other.AsInt();
		}

		virtual TypedData* operator|(const TypedData& other) const override
        {
            if (other.GetType() == Type::INT) {
                return new IntData(this->value | other.AsInt());
            }
            else {
                return nullptr;
            }
        }
	};

	class VectorData : public Data<Type::VECTOR, std::vector<Value>>
	{
	public:
		VectorData(const std::vector<Value>& value)
			: Data(value)
		{
		}

		VectorData(std::vector<Value>&& value)
			: Data(std::move(value))
		{
		}

		virtual const std::vector<Value> AsVector() const override
		{
			return this->value;
		}

		virtual TypedData* Clone() const override
		{
			return new VectorData(this->value);
		}

		virtual bool operator==(const TypedData& other) const override
        {
            return other.GetType() == Type::VECTOR && this->value == other.AsVector();
        }
	};

	struct Statics 
	{
		const std::vector<Value> emptyVector;
		const std::shared_ptr<EmptyData> empty = std::make_shared<EmptyData>();
		Statics() {}
	};

	static const Statics& statics()
	{
		static const Statics s{};
		return s;
	}

	Value::Value()
		: data(statics().empty)
	{
	}

	Value::Value(const Value& other)
	{
		this->data.reset(other.data->Clone());
	}

	Value& Value::operator=(const Value& other)
	{
		this->data.reset(other.data->Clone());
		return *this;
	}

	Value::Value(bool value)
		: data(std::make_shared<BoolData>(value))
	{
	}

	Value::Value(int value)
		: data(std::make_shared<IntData>(value))
	{
	}

	Value::Value(float value)
		: data(std::make_shared<FloatData>(value))
	{
	}

	Value::Value(const std::vector<Value>& values)
		: data(std::make_shared<VectorData>(values))
	{
	}

	Value::Value(std::vector<Value>&& values)
		: data(std::make_shared<VectorData>(std::move(values)))
	{
	}

	Type Value::GetType() const
	{
		return this->data->GetType();
    }

    bool Value::AsBool() const
    {
        return this->data->AsBool();
    }

    float Value::AsFloat() const
    {
        return this->data->AsFloat();
    }

    int Value::AsInt() const
    {
        return this->data->AsInt();
    }

	bool Value::operator==(const Value& other) const
	{
		return (*this->data) == (*other.data);
    }

    Value Value::operator|(const Value& other) const
    {
        TypedData* or = (*this->data) | (*other.data);
        Value result;
        result.data.reset(or);
        return result;
    }

	bool TypedData::AsBool() const
	{
		return false;
	}

	float TypedData::AsFloat() const
	{
		return 0.0f;
	}

	int TypedData::AsInt() const
	{
		return 0;
	}

	const std::vector<Value> TypedData::AsVector() const
	{
		return statics().emptyVector;
    }

    TypedData* TypedData::operator|(const TypedData& other) const
    {
        return nullptr;
    }
}
