#ifndef INVENTORY_H
#define INVENTORY_H

<<<<<<< HEAD
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
=======
#include <string>
#include <vector>

using std::vector;
using std::string;

class StudioProject;

class Inventory
{
	friend class Iron;
	friend class Titanium;
	friend class Mithril;
	friend class Bismuth;
public:
	Inventory();
	~Inventory();

	void AddingStuff();
	vector <string> inventory;
private:
	float _Iron = 10.0;
	float _Titanium = 10.0;
	float _Mithril = 10.0;
	float _Bismuth = 10.0;
	StudioProject *myscene;
};

#endif
>>>>>>> >Added inventory and some UI but not finished
