#include "example_list.h"
#include "example.h"
#include <vector>
#include <cstdlib>


void ExampleList::add(Example *ex)
{
	list.push_back(ex);
}

void ExampleList::remove(Example *ex)
{
}

Example *ExampleList::get_at(unsigned int i)
{
	return list.at(i);
}

Example *ExampleList::get_random()
{
	return list.at((unsigned int )(rand() % list.size()));
}

unsigned int ExampleList::get_size()
{
	return list.size();
}
