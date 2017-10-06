#pragma once
#include <math.h>

namespace ConstantValueData
{
	class Data
	{
	public:
		bool destroy = false; // every object should have a destroy so it can be destroyed 
		double value;


		// methods

		// adds this and other
		void add(Data& other)
		{
			value += other.value;
		}

		// subtracts other from this
		void sub(Data& other)
		{
			value -= other.value;
		}

		// multiplies this and other
		void mul(Data& other)
		{
			value *= other.value;
		}

		// divides this by other
		void div(Data& other)
		{
			value /= other.value;
		}

		// sets this to the absolute value of this
		void abs()
		{
			value = fabs(value);
		}

		// sets this to this modulo other (only for whole numbers)
		void mod(Data& other)
		{
			value = (int)value % (int)other.value;
		}

		// sets this to this to the power of other 
		void pow_(Data& other)
		{
			value = pow(value, other.value);
		}

		// applyFunctions
	};
}