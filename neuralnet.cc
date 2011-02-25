#include "neuralnet.h"

unsigned int NeuralNet::neuralnetid = 0;

NeuralNet::NeuralNet()
{
	id = neuralnetid++;
}

unsigned int NeuralNet::get_id()
{
	return id;
}

unsigned int NeuralNet::get_weights_size(
	unsigned int inputsize,
	unsigned int neuronperlayer,
	unsigned int hiddenlayers
)
{
	return 
		((inputsize + 1) * neuronperlayer)
		+ (neuronperlayer * (neuronperlayer + 1) * hiddenlayers)
		+ (neuronperlayer + 1)
	;
}

unsigned int NeuralNet::get_weights_layer_offset(
	unsigned int inputsize,
	unsigned int neuronperlayer,
	unsigned int num
)
{
	return 
		((inputsize + 1) * neuronperlayer)
		+ (neuronperlayer * (neuronperlayer + 1) * num)
	;
}
