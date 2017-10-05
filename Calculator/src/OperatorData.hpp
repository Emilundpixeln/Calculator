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

		bool apply_Operator_ALL(OperatorData::Data* prev)
	};
}
