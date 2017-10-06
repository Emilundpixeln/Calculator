#pragma once
#include "DataWrapper.hpp"
#include "OperatorData.hpp"
#include "ConstantValueData.hpp"
typedef bool(*ApplyFunction) (OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level);
#define dCast(t, p) (t::Data*) p->ptr


namespace OperatorFunction
{	
	constexpr int length = DataWrapper::Type::TYPE_COUNT;
	ApplyFunction functions[length][length] =
	{
		{
			// OperatorType, OperatorType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level)
			{
				return data->apply_Operator_ALL(dCast(OperatorData, prev));
			},
			
			// OperatorType, ConstantValueType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level)
			{
				return data->apply_Operator_ALL(dCast(OperatorData, prev));
			}

		},
		{
			// ConstantValueType, OperatorType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level)
			{
				
				return true;
			},

			// ConstantValueType, ConstantValueType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level)
			{
				return data->apply_ConstantValue_ConstantValue(dCast(ConstantValueData, prev), dCast(ConstantValueData, next), level);
			}

		}
	};
}

class Operator
{	
public:
	static bool apply(OperatorData::Data* data, DataWrapper* prev, DataWrapper* next, int level)
	{
		return false;
	}
};

