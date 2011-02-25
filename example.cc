#include "example.h"
#include "data.h"

Example::Example()
{
	input = 0;
	output = 0;
}

Example::Example(Data *d, double o)
{
	input = d;
	output = o;
}

void Example::set_input(Data *i)
{
	input = i;
}

void Example::set_output(double o)
{
	output = o;
}

Data *Example::get_input()
{
	return input;
}

double Example::get_output()
{
	return output;
}

