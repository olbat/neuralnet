#ifndef _EXAMPLE_LIST_H
#define _EXAMPLE_LIST_H

#include "example.h"
#include <vector>

class ExampleList
{
	private:
		std::vector<Example*> list;
	public:
		void add(Example *ex);
		void remove(Example *ex);
		Example *get_at(unsigned int i);
		Example *get_random();
		unsigned int get_size();
};

#endif
