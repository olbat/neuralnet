#include "layer_list.h"
#include "neuron.h"
#include "layer.h"
#include "data.h"

#include <iostream>

LayerList::LayerList(unsigned int maxsize)
{
	max_size = maxsize;
	size = 0;
	list = new Layer*[max_size];
}

LayerList::LayerList(const LayerList& ll)
{
	max_size = ll.max_size;
	size = ll.size;
	list = new Layer*[max_size];
	for (unsigned int i = 0; i < size; i++)
		list[i] = new Layer(*((const Layer *) ll.list[i]));
}

LayerList::~LayerList()
{
	for (unsigned int i = 0; i < get_size(); i++)
		delete get_at(i);
	delete[] list;
}

void LayerList::add(Layer *nn)
{
	list[size++ % max_size] = nn;
}

Layer *LayerList::get_at(unsigned int i)
{
	return list[i];
}

Layer *LayerList::get_head()
{
	return get_at(0);
}

Layer *LayerList::get_tail()
{
	return get_at(get_size()-1);
}

void LayerList::get_output(Data *input, Data *output)
{
	if (get_size() == 0)
		return;
	else if (get_size() == 1)
		get_at(0)->get_output(input,output);
	else
	{
		Data *tmpdatain, *tmpdataout;

		tmpdatain = input;
		for (unsigned int i = 0; i < get_size()-1; i++)
		{
			tmpdataout = new Data(get_layer_size(i));
			get_at(i)->get_output(tmpdatain,tmpdataout);
			if (i > 0)
				delete tmpdatain;
			tmpdatain = tmpdataout;
		}
		get_at(get_size()-1)->get_output(tmpdatain,output);
		delete tmpdatain;
	}
}

unsigned int LayerList::get_size()
{
	return size;
}

unsigned int LayerList::get_layer_size(unsigned int i)
{
	return get_at(i)->get_size();
}

void LayerList::reset()
{
	for (unsigned int i = 0; i < size; i++)
		get_at(i)->reset();
}

void LayerList::display()
{
	for (unsigned int i = 0; i < size; i++)
		get_at(i)->display();
}

void LayerList::perform_error(double deltaerr)
{
	/* Perform output error */
	Neuron *curp;
	for (unsigned int i = 0; i < get_tail()->get_size(); i++)
	{
		curp = get_tail()->get_at(i);
		curp->set_error(
			curp->get_actfunc()->derivation(curp->get_potential())
			/* * deltaerr */
		);
	}

	for (unsigned int i = size-1; i > 0; i--)
		get_at(i-1)->perform_error(get_at(i));
}

void LayerList::update_weights(Data *input, double oerror)
{
	Data *tmpdata;
	Layer *tmplayer;

	tmpdata = input;
	for (unsigned int i = 0; i < get_size(); i++)
	{
		get_at(i)->update_weights(tmpdata,oerror);
		
		if (i > 0)
			delete tmpdata;
		tmplayer = get_at(i);
		tmpdata = new Data(tmplayer->get_size());
		for (unsigned int j = 0; j < tmplayer->get_size(); j++)
			tmpdata->set_at(j,tmplayer->get_at(j)->get_output());
	}
	delete tmpdata;
}

void LayerList::update_weights(Data *input, double lambda, double error, bool b)
{
	Data *tmpdata;
	Layer *tmplayer;

	tmpdata = input;
	for (unsigned int i = 0; i < get_size(); i++)
	{
		get_at(i)->update_weights(tmpdata,lambda,error,b);
		
		if (i > 0)
			delete tmpdata;
		tmplayer = get_at(i);
		tmpdata = new Data(tmplayer->get_size());
		for (unsigned int j = 0; j < tmplayer->get_size(); j++)
			tmpdata->set_at(j,tmplayer->get_at(j)->get_output());
	}
	delete tmpdata;
}
