#include "multi_perceptron_layer_network.h"
#include "multi_layer_network.h"
#include "layer_perceptron.h"
#include "activation_function.h"
#include "af_sigmoid.h"
#include "af_identity.h"

#include <fstream>

MultiPerceptronLayerNet::MultiPerceptronLayerNet() : MultiLayerNet(0)
{
	initialized = false;
}

MultiPerceptronLayerNet::MultiPerceptronLayerNet(
	unsigned int is,
	unsigned int hl,
	unsigned int npl,
	double a
) : MultiLayerNet(hl+2)
{
	initialized = false;
	inputsize = is;
	hiddenlayers = hl;
	neuronsperlayer = npl;
	alpha = a;
	weights = 0;
	init();
}

MultiPerceptronLayerNet::MultiPerceptronLayerNet(
	const MultiPerceptronLayerNet& mpln
) : MultiLayerNet(mpln.hiddenlayers+2)
{
	deltaerror = mpln.deltaerror;

	initialized = false;
	inputsize = mpln.inputsize;
	hiddenlayers = mpln.hiddenlayers;
	neuronsperlayer = mpln.neuronsperlayer;
	alpha = mpln.alpha;
	weights = new Data(*((const Data *)mpln.weights));
	init();
/*
	layerlist = new LayerList(mpln.layerlist->max_size);
	
	for (unsigned int i = 0; i < mpln.layerlist->get_size(); i++)
	{
		layerlist->add(new PerceptronLayer(
			((PerceptronLayer *)mpln.layerlist->get_at(i))->nb,
			mpln.layerlist->get_at(i)->inputnb,
			mpln.layerlist->get_at(i)->af,
			weights,
			mpln.layerlist->get_at(i)->offset,
			false,
			mpln.layerlist->get_at(i)->alpha
		));
	}
*/
}

void MultiPerceptronLayerNet::init()
{
	if (!initialized)
	{
		bool needinit;
		if (!weights)
		{
			weights = new Data(
				NeuralNet::get_weights_size(
					inputsize,neuronsperlayer,hiddenlayers
				) + 1
			);
			needinit = true;
		}
		else
			needinit = false;
		add_layer(new PerceptronLayer(
			neuronsperlayer,
			inputsize,
			(ActivationFunction *) new AFSigmoid(),
			weights,
			1,
			needinit,
			alpha
		));
		for (unsigned int j = 0; j < hiddenlayers; j++)
		{
			add_layer(new PerceptronLayer(
				neuronsperlayer,
				neuronsperlayer,
				(ActivationFunction *) new AFSigmoid(),
				weights,
				NeuralNet::get_weights_layer_offset(
					inputsize,
					neuronsperlayer,
					j
				) + 1,
				needinit,
				alpha
			));
		}
		add_layer(new PerceptronLayer(
			1,
			neuronsperlayer,
			(ActivationFunction *) new AFIdentity(),
			weights,
			NeuralNet::get_weights_layer_offset(
				inputsize,
				neuronsperlayer,
				hiddenlayers
			) + 1,
			needinit,
			alpha
		));
	}
	initialized = true;
}

MultiPerceptronLayerNet::~MultiPerceptronLayerNet()
{
	delete weights;
}

void MultiPerceptronLayerNet::save(std::ofstream *ofs)
{
	ofs->write((char *)&max_size,sizeof(max_size));
	ofs->write((char *)&inputsize,sizeof(inputsize));
	ofs->write((char *)&hiddenlayers,sizeof(hiddenlayers));
	ofs->write((char *)&neuronsperlayer,sizeof(neuronsperlayer));
	ofs->write((char *)&alpha,sizeof(alpha));
	weights->save(ofs);
}

void MultiPerceptronLayerNet::load(std::ifstream *ifs)
{
	ifs->read((char *)&max_size,sizeof(max_size));
	ifs->read((char *)&inputsize,sizeof(inputsize));
	ifs->read((char *)&hiddenlayers,sizeof(hiddenlayers));
	ifs->read((char *)&neuronsperlayer,sizeof(neuronsperlayer));
	ifs->read((char *)&alpha,sizeof(alpha));
	weights = 0;
	MultiLayerNet::init();
	init();
	weights->load(ifs);
}
