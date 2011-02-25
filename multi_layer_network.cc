#include "multi_layer_network.h"
#include "data.h"
#include "layer.h"
#include "layer_list.h"
#include "neuron.h"
#include <iostream>
#include <limits>

MultiLayerNet::MultiLayerNet(unsigned int maxsize)
{
	max_size = maxsize;
	layerlist = 0;
	deltaerror = 0;
	init();
}

MultiLayerNet::MultiLayerNet(const MultiLayerNet& mln)
{
	max_size = mln.max_size;
	deltaerror = mln.deltaerror;
	layerlist = new LayerList(*((const LayerList *)mln.layerlist));
}

void MultiLayerNet::init()
{
	if (max_size > 0)
		layerlist = new LayerList(max_size);
}

MultiLayerNet::~MultiLayerNet()
{
	delete layerlist;
}

void MultiLayerNet::add_layer(Layer *l)
{
	layerlist->add(l);
}

void MultiLayerNet::learn(Example *e)
{
	double output;
	output = get_output(e->get_input());
	perform_error(output,e->get_output());
	update_weights(e->get_input(),output - e->get_output());
}

void MultiLayerNet::learn(Example *e, double lambda, bool b)
{
	double output;
	output = get_output(e->get_input());
	layerlist->perform_error(1);
	layerlist->update_weights(e->get_input(), lambda, output - e->get_output(), b);
}

void MultiLayerNet::learn(ExampleList *e, unsigned int iters)
{
	for (unsigned int i = 0; i < iters; i++)
		learn(e->get_random());
}

double MultiLayerNet::get_output(Data *input)
{
	double ret = 0;

	if (layerlist->get_size() > 0)
	{
		Data *tmpdata;
		tmpdata = new Data(layerlist->get_tail()->get_size());
		layerlist->get_output(input,tmpdata);

		ret = tmpdata->get_at(layerlist->get_tail()->get_size()-1);
		delete tmpdata;
	}

	return ret;
}

void MultiLayerNet::perform_error(double calc, double result)
{
	deltaerror = calc-result;
	layerlist->perform_error(deltaerror);
}

void MultiLayerNet::update_weights(Data *input, double oerror)
{
	layerlist->update_weights(input,oerror);
}

Layer *MultiLayerNet::get_input_layer()
{
	return layerlist->get_head();
}


Layer *MultiLayerNet::get_layer(unsigned int i)
{
	return layerlist->get_at(i);
}

Layer *MultiLayerNet::get_output_layer()
{
	return layerlist->get_tail();
}

double MultiLayerNet::get_delta_error()
{
	return deltaerror;
}

unsigned int MultiLayerNet::get_size()
{
	return layerlist->get_size();
}

void MultiLayerNet::reset()
{
	layerlist->reset();
}

void MultiLayerNet::display()
{
	std::cout << "MultiLayerNet:" << std::endl;
	layerlist->display();
}


double MultiLayerNet::test_get_best_weight()
{
	double ret;

	ret = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < layerlist->get_size(); i++)
	{
		if (layerlist->get_at(i)->test_get_best_weight() > ret)
			ret = layerlist->get_at(i)->test_get_best_weight();
	}

	return ret;
}
