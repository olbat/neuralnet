#ifndef _AF_SIGMOID_H
#define _AF_SIGMOID_H

#include "activation_function.h"

#define AF_SIGMOID_LAMBDA 2

class AFSigmoid: public ActivationFunction
{
	private:
		double lambda;
	public:
		AFSigmoid();
		AFSigmoid(double lambd);
		double get_value(double data);
		double derivation(double data);
};

#endif
