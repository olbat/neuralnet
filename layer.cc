#include "layer.h"
#include "neuralnet.h"
#include "neuron.h"

#include <iostream>
#include <limits>

unsigned int Layer::layerid = 0;

Layer::Layer(unsigned int maxsize)
{
	id = layerid++;

	max_size = maxsize;
	size = 0;
	list = new Neuron*[max_size];
}

Layer::Layer(const Layer& l)
{
	id = layerid++;
	max_size = l.max_size;
	size = l.size;
	list = 0;
}

Layer::~Layer()
{
	delete[] list;
}

void Layer::add(Neuron *nn)
{
	list[size++ % max_size] = nn;
}

Neuron *Layer::get_at(unsigned int i)
{
	return list[i];
}

unsigned int Layer::get_size()
{
	return size;
}

void Layer::display()
{
	std::cout << "  Layer " << id << ":" << std::endl;

	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << "    ";
		list[i]->display();
	}
}

void Layer::get_output(Data *input, Data *output)
{
	for (unsigned int i = 0; i < size; i++)
		output->set_at(i,get_at(i)->get_output(input));
}

void Layer::perform_error(Layer *next)
{
	for (unsigned int i = 0; i < get_size(); i++)
		get_at(i)->perform_error(next,i);
}

void Layer::update_weights(Data *input, double oerror)
{
	for (unsigned int i = 0; i < get_size(); i++) 
		get_at(i)->update_weights(input, oerror);
}

void Layer::update_weights(Data *input, double lambda, double error, bool b)
{
	for (unsigned int i = 0; i < get_size(); i++) 
		get_at(i)->update_weights(input,lambda,error,b);
}

void Layer::reset()
{
	for (unsigned int i = 0; i < get_size(); i++) 
		get_at(i)->reset();
}

double Layer::test_get_best_weight()
{
	double ret;

	ret = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < get_size(); i++)
	{
		if (get_at(i)->test_get_best_weight() > ret)
			ret = get_at(i)->test_get_best_weight();
	}

	return ret;
}
