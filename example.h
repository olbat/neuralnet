#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#include "data.h"


class Example
{
	private:
		Data *input;
		double output;
	public:
		Example();
		Example(Data *i, double o);
		void set_input(Data *i);
		void set_output(double o);
		Data *get_input();
		double get_output();
};

#endif
