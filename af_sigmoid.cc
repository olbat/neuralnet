#include "af_sigmoid.h"
#include <cmath>


AFSigmoid::AFSigmoid()
{
	lambda = 1;
}

AFSigmoid::AFSigmoid(double lambd)
{
	lambda = lambd;
}

double AFSigmoid::get_value(double data)
{
	return (1 / (1 + exp(-(lambda * data))));
}

#include <cstdlib>
double AFSigmoid::derivation(double data)
{
	double sig = get_value(data);
	return lambda * sig * (1 - sig);
//	return (get_value(data)*get_value(data))*(lambda * exp(-(lambda*data)));
}
