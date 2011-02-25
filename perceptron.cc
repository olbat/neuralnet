#include "perceptron.h"
#include "data.h"
#include "example.h"
#include "example_list.h"
#include "activation_function.h"
#include "af_identity.h"
#include "layer.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>

Perceptron::Perceptron(
	unsigned int inb,
	ActivationFunction *a,
	double alph = PERCEPTRON_ALPHA 
): Neuron(inb,a)
{
	alpha = alph;
	m = new Data(inputnb);
	for (unsigned int i = 0; i < inputnb; i++)
	{
		m->set_at(i,0);
		set_at(i,/* PERCEPTRON_DEFAULT_WEIGHT */
		(((rand() / ((float)RAND_MAX + 1))*2)-1)*0.1);
	}
}

Perceptron::Perceptron(
	unsigned int inb,
	ActivationFunction *a,
	Data *w,
	unsigned int off,
	bool init,
	double alph = PERCEPTRON_ALPHA
): Neuron(inb,a,w,off)
{
	alpha = alph;
	m = new Data(inputnb);
	for (unsigned int i = 0; i < inputnb; i++)
	{
		m->set_at(i,0);
		if (init)
		{
			set_at(i,/* PERCEPTRON_DEFAULT_WEIGHT */
			(((rand() / ((float)RAND_MAX + 1))*2)-1)*0.1);
		}
	}
}

Perceptron::Perceptron(const Perceptron& p) : Neuron(p)
{
	alpha = p.alpha;
}

Perceptron::~Perceptron()
{
	delete m;
}

void Perceptron::learn(Example *e)
{
	update_weights(e->get_input(),0);
}

void Perceptron::learn(Example *e, double lambda, bool b)
{
	update_weights(e->get_input(),0);
}

void Perceptron::learn(ExampleList *e, unsigned int iters)
{
	for (unsigned int i = 0; i < iters; i++)
		learn(e->get_random());
}

double Perceptron::get_output(Data *input)
{
	double sum;

	if (input->get_size() != inputnb-1)
		throw(std::runtime_error("Wrong size arguments"));
	sum = 0.0;
	for (unsigned int i = 0; i < inputnb; i++)
	{
		sum += (
			/* the bias */
			(i == inputnb-1 ? 1 : input->get_at(i))
			* get_at(i)
		);
	}
	potential = sum;
	output = actfunc->get_value(potential);

	return output;
}

void Perceptron::perform_error(Layer *next, unsigned int cur)
{
	error = 0;
	for (unsigned int i = 0; i < next->get_size(); i++)
		error += next->get_at(i)->get_error() * next->get_at(i)->get_at(cur);

	error *= get_actfunc()->derivation(potential);
}

void Perceptron::update_weights(Data *input, double oerror)
{
	double tmp;
	static const AFIdentity a;
	for (unsigned int i = 0; i < inputnb; i++)
	{
		tmp = get_at(i) -
		(
			alpha
			* (i == inputnb-1 ? 1 : input->get_at(i))
			* error
			* oerror
		);
		if (typeid(*actfunc) != typeid(a))
		{
			if (tmp > PERCEPTRON_WEIGHTS_THRESHOLD)
				tmp = PERCEPTRON_WEIGHTS_THRESHOLD;
			else if (tmp < -PERCEPTRON_WEIGHTS_THRESHOLD)
				tmp = -PERCEPTRON_WEIGHTS_THRESHOLD;
		}
		set_at(i,tmp);
	}
}

void Perceptron::update_weights(Data *input, double lambda, double oerror, bool b)
{
	double tmp;
	static const AFIdentity a;
	for (unsigned int i = 0; i < inputnb; i++)
	{
		m->set_at(i,
			(lambda * m->get_at(i)) 
			+ (b ? 
			((i == inputnb-1 ? 1 : input->get_at(i)) * error)
			: 0
			)
		);

		tmp = get_at(i) - (alpha * oerror * m->get_at(i));

		if (typeid(*actfunc) != typeid(a))
		{
			if (tmp > PERCEPTRON_WEIGHTS_THRESHOLD)
				tmp = PERCEPTRON_WEIGHTS_THRESHOLD;
			else if (tmp < -PERCEPTRON_WEIGHTS_THRESHOLD)
				tmp = -PERCEPTRON_WEIGHTS_THRESHOLD;
		}

		set_at(i,tmp);
	}
}

void Perceptron::display()
{
	std::cout << "Perceptron " << id << ": (error: " << error << ")" << std::endl;

	for (unsigned int i = 0; i < inputnb; i++)
	{
		std::cout << "\tw" << i << ": " << get_at(i) 
		<< (i == inputnb-1 ? " (bias)" : "") << std::endl;
	}
}

void Perceptron::reset()
{
	for (unsigned int i = 0; i < get_size(); i++)
		m->set_at(i,0.0);
}
