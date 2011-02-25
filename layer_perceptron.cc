#include "layer_perceptron.h"
#include "layer.h"
#include "perceptron.h"
#include "activation_function.h"
#include "af_sigmoid.h"


PerceptronLayer::PerceptronLayer(
	unsigned int nb,
	unsigned int inputnb,
	double alpha
) : Layer(nb)
{
	actfunc = new AFSigmoid(1);
	for (unsigned int i = 0; i < nb; i++)
		add(new Perceptron(inputnb,actfunc,alpha));
}

PerceptronLayer::PerceptronLayer(const PerceptronLayer& pl) : Layer(pl)
{
	actfunc = pl.actfunc;
	list = (Neuron **) new Perceptron*[max_size];
	for (unsigned int i = 0; i < size; i++)
		list[i] = new Perceptron(*((const Perceptron *)pl.list[i]));
	
}

PerceptronLayer::PerceptronLayer(
	unsigned int nb,
	unsigned int inputnb,
	ActivationFunction *af,
	double alpha
) : Layer(nb)
{
	actfunc = af;
	for (unsigned int i = 0; i < nb; i++)
		add(new Perceptron(inputnb,af,alpha));
}

PerceptronLayer::PerceptronLayer(
	unsigned int nb,
	unsigned int inputnb,
	ActivationFunction *af,
	Data *weights,
	unsigned int offset,
	bool init,
	double alpha
): Layer(nb)
{
	actfunc = af;
	for (unsigned int i = 0; i < nb; i++)
	{
		add(new Perceptron(
			inputnb,
			af,
			weights,
			offset + (i * (inputnb + 1)),
			init,
			alpha)
		);
	}
}

PerceptronLayer::~PerceptronLayer()
{
	delete actfunc;
	for (unsigned int i = 0; i < get_size(); i++)
		delete get_at(i);
}
