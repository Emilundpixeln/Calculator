#pragma once
#include "ConstantValueData.hpp"

namespace OperatorData
{
	enum Type
	{	
		addition,
		subtraction,
		multiplication,
		division,
		remainder,
		expont,
		absolute
	};

	class Data
	{	
	public:
		bool destroy = false; // every object should have a destroy so it can be destroyed 
		Type type;

		Data(Type _type)
		{
			type = _type;
		}

		~Data()
		{

		}

		// apply methods
		bool apply_Operator_ALL(OperatorData::Data* prev)
		{
			// turn + -, - +, - -, + + into -, -, +, +
			// doesn't care about next

			if (prev->type == OperatorData::addition)
			{
				// + - -> -, + + -> +
				if (this->type == OperatorData::addition || this->type == OperatorData::subtraction)
				{
					prev->destroy = true;
					return true;
				}
			}
			else if (prev->type == OperatorData::subtraction)
			{
				// - - -> +, - + -> -
				if (this->type == OperatorData::subtraction)
				{
					prev->type = OperatorData::addition;
					this->destroy = true;
					return true;
				}
				else if (this->type == OperatorData::addition)
				{
					this->destroy = true;
					return true;
				}
			}
			return false;
		}

		bool apply_ConstantValue_ConstantValue(ConstantValueData::Data* prev, ConstantValueData::Data* next, int level)
		{
			switch (type)
			{
			case OperatorData::addition:
				if (level != 3)
					return false;
				prev->add(*next);
				break;
			case OperatorData::subtraction:
				if (level != 3)
					return false;
				prev->sub(*next);
				break;
			case OperatorData::multiplication:
				if (level != 2)
					return false;
				prev->mul(*next);
				break;
			case OperatorData::division:
				if (level != 2)
					return false;
				prev->div(*next);
				break;
			case OperatorData::expont:
				if (level != 1)
					return false;
				prev->pow_(*next);
				break;
			default:
				return false;
			}
			// something changed
			// delete this and next
			this->destroy = true;
			next->destroy = true;
			return true;
		}
	};
}
