#ifndef _ACTIVATION_FUNCTION_H
#define _ACTIVATION_FUNCTION_H

class ActivationFunction
{
	public:
		virtual double get_value(double data) =0;
		virtual double derivation(double data) =0;
};

#endif
