#ifndef _NEURALNET_H
#define _NEURALNET_H

#include "data.h"
#include "example.h"
#include "example_list.h"

class NeuralNet
{
	public:
		static unsigned int get_weights_size(unsigned int inputsize,unsigned int neuronperlayer,unsigned int hiddenlayers);
		static unsigned int get_weights_layer_offset(unsigned int inputsize,unsigned int neuronperlayer,unsigned int num);
		NeuralNet();
		virtual ~NeuralNet() {};
		virtual void learn(Example *e) =0;
		/* with a trace */
		virtual void learn(Example *e, double lambda, bool b) =0;
		virtual void learn(ExampleList *e, unsigned int iters) =0;
		virtual double get_output(Data *input) =0;
		virtual void reset() =0;
		virtual void display() =0;
		virtual unsigned int get_size() =0;
		virtual double test_get_best_weight() =0;
		unsigned int get_id();
	protected:
		static unsigned int neuralnetid;
		unsigned int id;
};

#endif
