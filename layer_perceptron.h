#ifndef _LAYER_PERCEPTRON_H
#define _LAYER_PERCEPTRON_H

#include "layer.h"
#include "perceptron.h"
#include "activation_function.h"

class PerceptronLayer: public Layer
{
	private:
		ActivationFunction *actfunc;
	public:
		PerceptronLayer(unsigned int nb,unsigned int inputnb,double alpha = PERCEPTRON_ALPHA);
		PerceptronLayer(unsigned int nb, unsigned int inputnb, ActivationFunction *af,double alpha = PERCEPTRON_ALPHA);
		PerceptronLayer(unsigned int nb, unsigned int inputnb, ActivationFunction *af, Data *weights, unsigned int offset, bool init, double alpha = PERCEPTRON_ALPHA);
		PerceptronLayer(const PerceptronLayer& pl);
		~PerceptronLayer();
};

#endif
