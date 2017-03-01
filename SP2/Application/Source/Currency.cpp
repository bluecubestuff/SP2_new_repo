#include "Currency.h"

Currency::Currency() : value(0), bismuth(0), titanium(0), mithril(0), iron(0) {}

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

void Currency::add_mineral(std::string mineral_name)
{
	int num_min;
	srand((unsigned)(time(NULL)));
	num_min = Math::RandIntMinMax(1, 3);

	if (mineral_name == "iron")
	{
		iron += num_min;
	}
	else if (mineral_name == "mithril")
	{
		mithril += num_min;
	}
	else if (mineral_name == "titanium")
	{
		titanium += num_min;
	}
	else if (mineral_name == "bismuth")
	{
		bismuth += num_min;
	}
}


int Currency::get_mineral(std::string mName)
{
	if (mName == "iron")
	{
		return iron;
	}
	else if (mName == "mithril")
	{
		return mithril;
	}
	else if (mName == "titanium")
	{
		return titanium;
	}
	else if (mName == "bismuth")
	{
		return bismuth;
	}

	return 0;
}

void Currency::set_mineral(std::string mName)
{
	if (mName == "iron")
	{
		iron -= 1;
	}
	else if (mName == "mithril")
	{
		mithril -= 1;
	}
	else if (mName == "titanium")
	{
		titanium -= 1;
	}
	else if (mName == "bismuth")
	{
		bismuth -= 1;
	}
}