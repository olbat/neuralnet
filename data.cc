#include "data.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

Data::Data()
{
	size = 0;
	data = 0;
}

Data::Data(unsigned int s)
{
	size = s;
	data = 0;
	init();
}

Data::Data(unsigned int s, double *t)
{
	size = s;
	data = 0;
	init();
	for(unsigned int i = 0; i < size; i++)
		data[i] = t[i];
}

Data::Data(const Data& d)
{
	size = d.size;
	data = new double[size];
	for (unsigned int i = 0; i < size; i++)
		data[i] = d.data[i];
	printf("YOUPILOL\n");
}

void Data::init()
{
	if (!data)
		data = new double[size];
}

Data::~Data()
{
	if (data)
		delete[] data;
}

double Data::get_at(unsigned int i)
{
	return data[i];
}

void Data::set(Data *d)
{
	if (d->get_size() != size)
		throw(std::runtime_error("Wrong size arguments"));

	for (unsigned int i = 0; i < size; i++)
		data[i] = d->get_at(i);
}

void Data::set_at(unsigned int i, double val)
{
	data[i] = val;;
}

unsigned int Data::get_size()
{
	return size;
}

void Data::save(std::ofstream *ofs)
{
	ofs->write((char *)&size,sizeof(size));
	for (unsigned int i = 0; i < size; i++)
		ofs->write((char *)(data + i),sizeof(data[i])); 
}

void Data::load(std::ifstream *ifs)
{
	ifs->read((char *)&size,sizeof(size));
	init();
	for (unsigned int i = 0; i < size; i++)
		ifs->read((char *)(data + i),sizeof(data[i])); 
}
