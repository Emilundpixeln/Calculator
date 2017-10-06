#pragma once
#include "TreeComponent.hpp"
#include <vector>

class Tree
{
	std::vector<TreeComponent>* components;
public:
	bool dirty = false;

	Tree(const std::vector<TreeComponent>& l)
	{
		components = new std::vector<TreeComponent>(l);
	}

	bool apply() {
		// makes things easier
		std::vector<TreeComponent>& c = *components;

		// go through all the levels
		for (int level = 0; level < 4; level++)
		{
			dirty = true;
			// repeat until nothing changes
			while (dirty) 
			{
				for (size_t i = 0; i < c.size(); i++)
				{	
					// make sure that we don't go out of bounds
					if (i == 0)
						dirty = c[i].apply(nullptr, &c[i + 1].data, level);
					else if (i == c.size() - 1)
						dirty = c[i].apply(&c[i - 1].data, nullptr, level);
					else
						dirty = c[i].apply(&c[i - 1].data, &c[i + 1].data, level);
				}
				if (dirty)
				{
					// erase all the components which sgould get destroyed
					for (size_t i = 0; i < c.size(); i++)
						if (c[i].destroy())
						{
							c.erase(c.begin() + i);
							i--;
						}

				}
			}
			return true;
		}
	}

	~Tree()
	{
		delete[] components;
	}

};