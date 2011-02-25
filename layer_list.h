#ifndef _LAYER_LIST_H
#define _LAYER_LIST_H

#include "layer.h"
#include "data.h"
#include <map>

class LayerList
{
	private:
		Layer **list;
		unsigned int max_size;
		unsigned int size;
	public:
		LayerList(unsigned int maxsize);
		LayerList(const LayerList& ll);
		virtual ~LayerList();
		void add(Layer *nn);
		Layer *get_at(unsigned int i);
		Layer *get_head();
		Layer *get_tail();
		void get_output(Data *input, Data *output);
		unsigned int get_size();
		void perform_error(double deltaerr);
		void reset();
		void update_weights(Data *input, double oerror);
		void update_weights(Data *input,double lambda,double error,bool b);
		void display();
	protected:
		unsigned int get_layer_size(unsigned int i);
};

#endif
