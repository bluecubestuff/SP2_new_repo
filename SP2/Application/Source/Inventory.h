#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <iostream>
#include <vector>

using std::vector;

class Inventory
{
public:
	
	Inventory();
	~Inventory();

	vector<Item*> playerInventory;
	void addItem(Item* item, int value);
	void removeItem(string itemName, int value);
	int getter(string itemName);
	bool inventoryOpen;
	void setter(string itemName, int value);
	bool ItemExistsInInventory(string itemName);
	float posY;
	
private:
	unsigned int credits;
	unsigned int amountOfIron;
	unsigned int amountOfTitanium;
	unsigned int amountOfMithril;
	unsigned int amountOfBismuth;
};

#endif
