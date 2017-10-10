#include "Tree.hpp"
#include <vector>
#include <iostream>

/*
// Add /FORCE:MULTIPLE  to linker command line options	TODO: find out if this is a good way
// Each Typer eg OperatorType, ConstantValueType is a Class which has methods for appling.
// More complex types will have method to interact with less complex types eg Polynomial.add(ConstantValue) not ConstantValue.add(Polynomial) so that the type stays
// when the tree does an apply it will call apply of each component first with level 0 then 1 then 2 ...
// the level indicates which operations will be called:
//	0: 1: power 2: mul, div 3: addition, subtraction
*/

/* TODO

*/
int main()
{
	std::vector<TreeComponent> comp;
	ConstantValueData::Data* p = &ConstantValueData::Data(1);
	comp.push_back(TreeComponent(p));
	comp.push_back(TreeComponent(&OperatorData::Data(OperatorData::addition)));
	comp.push_back(TreeComponent(&ConstantValueData::Data(2)));
	Tree tree(comp);
	tree.apply();

	std::cin.get();
}

