#ifndef _LAYER_H
#define _LAYER_H

#include "data.h"
#include <vector>

class Neuron;
class Layer
{
	friend class boost::serialization::access;
	friend class PerceptronLayer;
	private:
		Neuron **list;
		unsigned int max_size;
		unsigned int size;
	public:
		Layer(unsigned int maxsize);
		Layer(const Layer& l);
		virtual ~Layer();
		void add(Neuron *nn);
		Neuron *get_at(unsigned int i);
		void get_output(Data *input, Data *output);
		unsigned int get_size();
		void perform_error(Layer *next);
		void update_weights(Data *input, double oerror);
		void update_weights(Data *input,double lambda,double error,bool b);
		double test_get_best_weight();
		void reset();
		void display();
	protected:
		static unsigned int layerid;
		unsigned int id;
};

#endif
