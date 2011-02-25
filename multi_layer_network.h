#ifndef _MULTI_LAYER_NETWORK_H
#define _MULTI_LAYER_NETWORK_H

#include "neuralnet.h"
#include "layer.h"
#include "layer_list.h"

class MultiLayerNet: public NeuralNet
{
	friend class MultiPerceptronLayerNet;
	private:
		double deltaerror;
	public:
		MultiLayerNet(unsigned int maxsize);
		MultiLayerNet(const MultiLayerNet& mln);
		virtual ~MultiLayerNet();

		double get_delta_error();
		Layer *get_input_layer();
		Layer *get_layer(unsigned int);
		Layer *get_output_layer();
		unsigned int get_size();

		virtual void add_layer(Layer *l);
		void learn(Example *e);
		void learn(Example *e, double lambda, bool b);
		void learn(ExampleList *e, unsigned int iters);
		double get_output(Data *input);
		double test_get_best_weight();
		void reset();
		void display();
	protected:
		LayerList *layerlist;
		unsigned int max_size;
		void init();
		void update_weights(Data *input, double oerror);
		void perform_error(double calc, double result);
};

#endif
