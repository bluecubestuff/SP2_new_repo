#include "Currency.h"

Currency::Currency() : value(0), playerCurrency(0){}

Currency::~Currency() {}

Currency* Currency::get_instance()
{
	if (!instance)
	{
		instance = new Currency;
	}
	return instance;
}

int Currency::value_getter()
{
	return value;
}

void Currency::value_setter(int sValue)
{
	value = sValue;
}

void Currency::value_adder(int v)
{
	value += v;
}

void Currency::add_playerCurrency(int playerCurr)
{
	playerCurrency += playerCurr;
}

int Currency::playerCurrency_getter()
{
	return playerCurrency;
}