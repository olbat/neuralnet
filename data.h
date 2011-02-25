#ifndef _DATA_H
#define _DATA_H

#include <boost/archive/text_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp> 
#include <fstream>

class Data
{
	friend class boost::serialization::access;
	private:
		unsigned int size;
		double *data;
	public:
		Data();
		Data(unsigned int s);
		Data(unsigned int s, double *t);
		Data(const Data& d);
		virtual ~Data();
		double get_at(unsigned int i);
		void set(Data *d);
		void set_at(unsigned int i, double val);
		unsigned int get_size();
		void save(std::ofstream *ofs);
		void load(std::ifstream *ifs);
	protected:
		void init();
		template <class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & size;
			init();
			for (unsigned int i = 0; i < size; i++)
				ar & data[i]; 
		}
};

#endif
