#include "Item.h"
#include "Weapon.h"

Item::Item(string iName, unsigned value, int iDurability) : itemName(iName), itemValue(value), itemDurability(iDurability) {}

Item::~Item() {}

unsigned Item::getValue()
{
	return this->itemValue;
}

int Item::getDurability()
{
	return this->itemDurability;
}

string Item::getName()
{
	return this->itemName;
}