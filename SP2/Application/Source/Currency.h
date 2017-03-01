#ifndef _CURRENCY_H
#define _CURRENCY_H

class Currency
{
public:

	~Currency();

	static Currency* get_instance();

	int value_getter();
	void value_setter(int);
	void value_adder(int);

private:

	Currency();
	static Currency* instance;
	int value;
};


#endif