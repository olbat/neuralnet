#ifndef _AF_IDENTITY_H
#define _AF_IDENTITY_H

#include "activation_function.h"

class AFIdentity: public ActivationFunction
{
	public:
		double get_value(double data);
		double derivation(double data);
};

#endif
