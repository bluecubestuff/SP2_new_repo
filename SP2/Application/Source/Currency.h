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
	
	void add_playerCurrency(int);
	int playerCurrency_getter();
private:

	Currency();
	static Currency* instance;
	int value;
	int playerCurrency;
};


#endif