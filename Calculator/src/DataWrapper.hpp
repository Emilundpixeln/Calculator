#pragma once
#include "OperatorData.hpp"


struct DataWrapper
{
	enum Type
	{
		OperatorType,
		ConstantValueType,
		TYPE_COUNT
	};

	Type type;
	void* ptr;

	~DataWrapper()
	{
		switch (type)
		{
		case OperatorType:
			delete (OperatorData::Data*)ptr;
			break;
		case ConstantValueType:
			break;
		default:
			break;
		}
	}
};