#include "af_identity.h"


double AFIdentity::get_value(double data)
{
	return data;
}

double AFIdentity::derivation(double data)
{
	return 1;
}
