#pragma once

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
		factorial,
		absolute,

	};

	struct Data
	{	
		bool destroy = false; // every object should have a destroy so it can be destroyed 
		Type type;
	};
}