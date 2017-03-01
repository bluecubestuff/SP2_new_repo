#ifndef _CURRENCY_H
#define _CURRENCY_H

#include "string"
#include "MyMath.h"

class Currency
{
public:

	~Currency();

	static Currency* get_instance();

	int value_getter();
	void value_setter(int);
	void value_adder(int);
	void add_mineral(std::string);
	int get_mineral(std::string);
	void set_mineral(std::string);

private:

	Currency();
	static Currency* instance;
	int value;

	int bismuth;
	int titanium;
	int mithril;
	int iron;
};


#endif