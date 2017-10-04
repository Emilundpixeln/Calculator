#pragma once
#include "DataWrapper.hpp"
#include "OperatorData.hpp"
#include "ConstantValueData.hpp"
typedef bool(*ApplyFunction) (OperatorData::Data* data, DataWrapper* prev, DataWrapper* next);

namespace OperatorFunction
{	
	constexpr int length = DataWrapper::Type::TYPE_COUNT;
	ApplyFunction functions[length][length] =
	{
		{
			// OperatorType, OperatorType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next)
			{
				// turn + -, - +, - -, + + into -, -, +, +
				// doesn't care about next

				OperatorData::Data& thisData = *data;
				OperatorData::Data& prevData = *(OperatorData::Data*)(prev->ptr);

				if (prevData.type == OperatorData::addition)
				{
					// + - -> -, + + -> +
					if (thisData.type == OperatorData::addition || thisData.type == OperatorData::subtraction)
					{
						prevData.destroy = true;
						return true;
					}
				}
				else if (prevData.type == OperatorData::subtraction)
				{
					// - - -> +, - + -> -
					if (thisData.type == OperatorData::subtraction)
					{
						prevData.type = OperatorData::addition;
						thisData.destroy = true;
						return true;
					}
					else if (thisData.type == OperatorData::addition)
					{
						thisData.destroy = true;
						return true;
					}
				}
				return false;
			},
			
			// OperatorType, ConstantValueType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next)
			{
				// turn + -, - +, - -, + + into -, -, +, +
				// doesn't care about next
				//same as above

				OperatorData::Data& thisData = *data;
				OperatorData::Data& prevData = *(OperatorData::Data*)(prev->ptr);

				if (prevData.type == OperatorData::addition)
				{
					// + - -> -, + + -> +
					if (thisData.type == OperatorData::addition || thisData.type == OperatorData::subtraction)
					{
						prevData.destroy = true;
						return true;
					}
				}
				else if (prevData.type == OperatorData::subtraction)
				{
					// - - -> +, - + -> -
					if (thisData.type == OperatorData::subtraction)
					{
						prevData.type = OperatorData::addition;
						thisData.destroy = true;
						return true;
					}
					else if (thisData.type == OperatorData::addition)
					{
						thisData.destroy = true;
						return true;
					}
				}
				return false;
			}

		},
		{
			// ConstantValueType, OperatorType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next)
			{
			return true;
			},

			// ConstantValueType, ConstantValueType
			[](OperatorData::Data* data, DataWrapper* prev, DataWrapper* next)
			{
				return true;
			}

		}
	};
}

class Operator
{	
public:
	/*static bool apply(OperatorData::Data* data, DataWrapper* prev, DataWrapper* next) // TODO: implement https://stackoverflow.com/questions/14827914/is-there-any-design-pattern-to-avoid-a-nested-switch-case?rq=1
	{
		OperatorData::Data& thisData = *data;

		switch (prev->type)
		{
		case DataWrapper::OperatorType:
		{ //scope is needed to define variables inside of a case
			OperatorData::Data& prevData = *(OperatorData::Data*)(prev->ptr);

			// turn + -, - +, - -, + + into -, -, +, +
			if (prevData.type == OperatorData::addition)
				// + - -> -, + + -> +
				if (thisData.type == OperatorData::addition || thisData.type == OperatorData::subtraction)
				{
					prevData.destroy = true;
					return true;
				}
				else if (prevData.type == OperatorData::subtraction)
					// - - -> +, - + -> -
					if (thisData.type == OperatorData::subtraction)
					{
						prevData.type = OperatorData::addition;
						thisData.destroy = true;
						return true;
					}
					else if (thisData.type == OperatorData::addition)
					{
						thisData.destroy = true;
						return true;
					}
		}
		case DataWrapper::ConstantValueType:
		{
			ConstantValueData::Data& prevData = *(ConstantValueData::Data*)(prev->ptr);
		}
		}
	}*/
};
