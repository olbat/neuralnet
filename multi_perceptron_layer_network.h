#ifndef _MULTI_PERCEPTRON_LAYER_NETWORK_H
#define _MULTI_PERCEPTRON_LAYER_NETWORK_H

#include "multi_layer_network.h"
#include "data.h"
#include <boost/archive/text_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp> 
#include <boost/serialization/extended_type_info.hpp>
#include <fstream>

class MultiPerceptronLayerNet: public MultiLayerNet
{
	friend class boost::serialization::access;
	private:
		Data *weights;
		unsigned int inputsize;
		unsigned int hiddenlayers;
		unsigned int neuronsperlayer;
		double alpha;
		bool initialized;
	public:
		MultiPerceptronLayerNet();
		MultiPerceptronLayerNet(unsigned int inputsize, unsigned int hiddenlayers, unsigned int neuronsperlayer, double alpha);
		MultiPerceptronLayerNet(const MultiPerceptronLayerNet& mpln);
		~MultiPerceptronLayerNet();
		void save(std::ofstream *ofs);
		void load(std::ifstream *ifs);
	protected:
		void init();
		template <class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{ 
			ar & max_size;
			ar & inputsize;
			ar & hiddenlayers;
			ar & neuronsperlayer;
			ar & alpha;
			ar & weights;
			MultiLayerNet::init();
			init();
		}
};

#endif
