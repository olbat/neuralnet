#include "data.h"
#include "example.h"
#include "example_list.h"
#include "perceptron.h"
#include "af_identity.h"
#include "af_sigmoid.h"
#include "layer.h"
#include "layer_perceptron.h"
#include "multi_layer_network.h"
#include "multi_perceptron_layer_network.h"

#include <boost/archive/text_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

double function(double x, double y)
{
	//return x * (y > 0 ? 1 : 0);
	double x2 = x*x, y2 = y*y;
	return (x2 - y2) / (x2 + y2);
	//return (((x2 - y2) / (x2 + y2))+1)/2;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "usage: " << argv[0] 
			<< " <nb_iter> <output_file>" << std::endl;
		exit(0);
	}

	std::ofstream output;
	if (argc > 2)
		output.open(argv[2]);
	
	ExampleList examplelist;
	double val[2];

	for (double i = 0; i <= 1; i+=0.1f)
	{
		for (double j = -1; j <= 1; j+=0.1f)
		{
			val[0] = i;
			val[1] = j;
			examplelist.add(new Example(new Data(2,val),function(i,j)));
		}
	}
	AFSigmoid afs(1);
	AFIdentity afi;

	MultiPerceptronLayerNet *multil = new MultiPerceptronLayerNet(2,1,4,0.1);
	srand(time(0));

	for (int i = 0; i < atoi(argv[1]); i++)
	{
		multil->learn(&examplelist,1);
		if (argc > 2)
		{
			/*
			output
			<< i 
			<< " " << multil.get_output(data[0])
			<< " " << multil.get_output(data[1])
			<< " " << multil.get_output(data[2])
			<< " " << multil.get_output(data[3])

			<< " " << multil.get_layer(0)->get_at(0)->get_weights()
				->get_at(0)
			<< " " << multil.get_layer(0)->get_at(0)->get_weights()
				->get_at(1)
			<< " " << multil.get_layer(0)->get_at(0)->get_weights()
				->get_at(2)

			<< " " << multil.get_layer(0)->get_at(1)->get_weights()
				->get_at(0)
			<< " " << multil.get_layer(0)->get_at(1)->get_weights()
				->get_at(1)
			<< " " << multil.get_layer(0)->get_at(1)->get_weights()
				->get_at(2)

			<< " " << multil.get_layer(1)->get_at(0)->get_weights()
				->get_at(0)
			<< " " << multil.get_layer(1)->get_at(0)->get_weights()
				->get_at(1)
			<< " " << multil.get_layer(1)->get_at(0)->get_weights()
				->get_at(2)

			<< " " << multil.get_layer(0)->get_at(0)->get_potential()
			<< " " << multil.get_layer(0)->get_at(1)->get_potential()
			<< " " << multil.get_layer(1)->get_at(0)->get_potential()
			<< " " << multil.get_delta_error()
			<< std::endl
			;
			*/
		}
	}
	MultiPerceptronLayerNet *multilnew = new MultiPerceptronLayerNet(*((const MultiPerceptronLayerNet *)multil));
	for (int i = 0; i < 1000; i++)
		multil->learn(&examplelist,1);

	if (argc > 2)
		output.close();
	for (unsigned int i = 0; i < examplelist.get_size(); i++)
	{
		std::cout
		<< "(" << examplelist.get_at(i)->get_input()->get_at(0)
		<< " " << examplelist.get_at(i)->get_input()->get_at(1)
		<< ") -> " << examplelist.get_at(i)->get_output()
		<< " / " << multil->get_output(examplelist.get_at(i)->get_input())
		<< std::endl
		;
	}
	//std::ofstream of;
	//of.open("test.carch", std::ios::out | std::ios::binary);
/*
	boost::archive::text_oarchive oa(of); 
	//oa.register_type(static_cast<MultiPerceptronLayerNet *>(NULL)); 
	oa << *((const MultiPerceptronLayerNet *)multil);
*/
	//multil->save(&of);
	//of.close();
//////////
	//std::ifstream inf;
	//inf.open("test.carch", std::ios::in | std::ios::binary);
/*
	boost::archive::text_iarchive ia(inf); 
	//ia.register_type(static_cast<MultiPerceptronLayerNet *>(NULL)); 
	ia >> *multilnew;
*/
	//multilnew->load(&inf);
	//inf.close();

	std::cout << "### INPUT ###" << std::endl;
	for (unsigned int i = 0; i < examplelist.get_size(); i++)
	{
		std::cout
		<< "(" << examplelist.get_at(i)->get_input()->get_at(0)
		<< " " << examplelist.get_at(i)->get_input()->get_at(1)
		<< ") -> " << examplelist.get_at(i)->get_output()
		<< " / " << multilnew->get_output(examplelist.get_at(i)->get_input())
		<< std::endl
		;
	}
	

	return 0;
}
