#ifndef _PERCEPTRON_H
#define _PERCEPTRON_H

#include "neuron.h"
#include "activation_function.h"
#include "data.h"
#include "example.h"
#include "example_list.h"

#define PERCEPTRON_DEFAULT_WEIGHT 0
#define PERCEPTRON_ALPHA 0.1
#define PERCEPTRON_WEIGHTS_THRESHOLD 4.0

class Perceptron: public Neuron
{
	private:
		double alpha;
		Data *m;
	public:
		Perceptron(unsigned int inb, ActivationFunction *a, double alph);
		Perceptron(unsigned int inb,ActivationFunction *a,Data *w,unsigned int off, bool init, double alph);
		Perceptron(const Perceptron& p);
		~Perceptron();
		void learn(Example *e);
		void learn(Example *e,double lambda, bool b);
		void learn(ExampleList *e, unsigned int iters);
		double get_output(Data *input);
		void perform_error(Layer *next, unsigned int cur);
		void update_weights(Data *input,double lambda,double error,bool b);
		void update_weights(Data *input, double oerror);
		void reset();
		void display();
};

#endif
