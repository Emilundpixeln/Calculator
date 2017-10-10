#pragma once
#include "DataWrapper.hpp"
#include "OperatorData.hpp"
#include "Operator.hpp"
#include "ConstantValueData.hpp"
#include "ConstantValue.hpp"

#include <iostream>


class TreeComponent
{

public:

	DataWrapper data;

	TreeComponent(OperatorData::Data* p) {
		data.ptr = (void*)p;
		data.type = DataWrapper::OperatorType;
	}

	TreeComponent(ConstantValueData::Data* p) {
		data.ptr = (void*)p;
		data.type = DataWrapper::ConstantValueType;
	}


	// level is which operations should run eg 0: abs 1: power 2: mul, div...
	bool apply(DataWrapper* prev, DataWrapper* next, int level) {
		bool dirty = false;

		switch (data.type)
		{
		case DataWrapper::OperatorType:
			dirty = Operator::apply((OperatorData::Data*)data.ptr, prev, next, level);
			break;
		case DataWrapper::ConstantValueType:

			break;
		default:
			break;
		}

		return dirty;
	}

	~TreeComponent()
	{
		switch (data.type)
		{
		case DataWrapper::OperatorType:
			delete (OperatorData::Data*)data.ptr;
			break;
		case DataWrapper::ConstantValueType:
			delete (ConstantValueData::Data*)data.ptr;
			break;
		default:
			break;
		}
	}

	// return if this should be destroyed
	bool destroy()
	{
		switch (data.type)
		{
		case DataWrapper::OperatorType:
			return ((OperatorData::Data*)data.ptr)->destroy;
		case DataWrapper::ConstantValueType:
			return ((ConstantValueData::Data*)data.ptr)->destroy;
			return false;
		default:
			return false;
		}
	}
};