#include "neuron.h"
#include "data.h"
#include "example.h"
#include "example_list.h"
#include "activation_function.h"
#include <cmath>
#include <limits>


Neuron::Neuron(unsigned int inb, ActivationFunction *a)
{
	/* 1 input for the bias */
	inputnb = inb + 1;
	weights = new Data(inputnb);
	error = 0;
	potential = 1;
	output = 0;
	actfunc = a;
	offset = 0;
}

#include <iostream>
Neuron::Neuron(
	unsigned int inb,
	ActivationFunction *a,
	Data *w,
	unsigned int off
)
{
	inputnb = inb + 1;
	offset = off;
	weights = w;
	actfunc = a;
	error = 0;
	potential = 1;
	output = 0;
}

Neuron::Neuron(const Neuron &n)
{
	inputnb = n.inputnb;
	weights = new Data(*((const Data *)n.weights));
	error = n.error;
	potential = n.potential;
	output = n.output;
	actfunc = n.actfunc;
	offset = n.offset;
}

Neuron::~Neuron()
{
	if (offset <= 0)
		delete weights;
}

double Neuron::get_potential()
{
	return potential;
}

double Neuron::get_output()
{
	return output;
}

double Neuron::get_error()
{
	return error;
}

void Neuron::set_error(double val)
{
	error = val;
}

double Neuron::get_at(unsigned int i)
{
	return weights->get_at(i + offset);
}

void Neuron::set_at(unsigned int i, double v)
{
	weights->set_at(i + offset, v);
}

ActivationFunction *Neuron::get_actfunc()
{
	return actfunc;
}

unsigned int Neuron::get_size()
{
	return 1;
}

double Neuron::test_get_best_weight()
{
	double ret;

	ret = std::numeric_limits<double>::min();

	for (unsigned int i = 0; i < inputnb; i++)
	{
		if (std::abs(get_at(i)) > ret)
			ret = std::abs(get_at(i));
	}

	return ret;
}
