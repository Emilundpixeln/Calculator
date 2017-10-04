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
		std::vector<TreeComponent>& c = *components;
		dirty = true;
		while (dirty)
		{
			for (size_t i = 0; i < c.size(); i++)
			{
				if (i == 0)
					dirty = c[i].apply(nullptr, &c[i + 1].data);
				else if (i == c.size() - 1)
					dirty = c[i].apply(&c[i - 1].data, nullptr);
				else
					dirty = c[i].apply(&c[i - 1].data, &c[i + 1].data);	
			}
			if (dirty)
			{
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

	~Tree()
	{
		delete[] components;
	}

};