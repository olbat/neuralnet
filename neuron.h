#ifndef _NEURON_H
#define _NEURON_H

#include "neuralnet.h"
#include "data.h"
#include "example.h"
#include "example_list.h"
#include "activation_function.h"

class Layer;
class Neuron: public NeuralNet
{
	friend class boost::serialization::access;
	protected:
		Data *weights;
		int offset;
		unsigned int inputnb;
		ActivationFunction *actfunc;
		double error;
		double potential;
		double output;
	
	public:
		Neuron(unsigned int inb,ActivationFunction *a,Data *w,unsigned int off);
		Neuron(unsigned int inb, ActivationFunction *a);
		Neuron(const Neuron &n);
		virtual ~Neuron();
		double get_potential();
		double get_output();
		double get_error();
		void set_error(double val);
		double get_at(unsigned int i);
		void set_at(unsigned int i, double v);
		//Data *get_weights();
		ActivationFunction *get_actfunc();
		unsigned int get_size();
		double test_get_best_weight();

		virtual void learn(Example *e) =0;
		virtual void learn(Example *e,double lambda, bool b) =0;
		virtual void learn(ExampleList *e, unsigned int iters) =0;
		virtual double get_output(Data *input) =0;
		virtual void perform_error(Layer *next, unsigned int cur) =0;
		virtual void update_weights(Data *input, double oerror) =0;
		virtual void update_weights(Data *input, double lambda, double oerror, bool b) =0;
		virtual void reset() =0;
		virtual void display() =0;
};

#endif
