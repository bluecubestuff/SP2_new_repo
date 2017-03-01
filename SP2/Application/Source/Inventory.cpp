#include "Inventory.h"

Inventory::Inventory()
{
	inventoryOpen = false;
	amountOfBismuth = 0;
	amountOfIron = 0;
	amountOfMithril = 0;
	amountOfTitanium = 0;
	posY = 17;
}

Inventory::~Inventory()
{

}

int Inventory::getter(string itemName)
{
	if (itemName == "iron")
	{
		return amountOfIron;
	}
	else if (itemName == "titanium")
	{
		return amountOfTitanium;
	}
	else if (itemName == "mithril")
	{
		return amountOfMithril;
	}
	else if (itemName == "bismuth")
	{
		return amountOfBismuth;
	}
	else if (itemName == "credits")
	{
		return credits;
	}
}

void Inventory::setter(string itemName, int value)
{
	if (itemName == "iron")
	{
		amountOfIron = amountOfIron + value;
	}
	else if (itemName == "titanium")
	{
		amountOfTitanium = amountOfTitanium + value;
	}
	else if (itemName == "mithril")
	{
		amountOfMithril = amountOfMithril + value;
	}
	else if (itemName == "bismuth")
	{
		amountOfBismuth = amountOfBismuth + value;
	}
	else if (itemName == "credits")
	{
		credits = credits + value;
	}
}

void Inventory::addItem(Item* item, int value)
{
	if (getter(item->getName()) == 0)
	{
		std::cout << "item added" << std::endl;
		playerInventory.push_back(item);
		setter(item->getName(), value);
	}
	else
	{
		setter(item->getName(), value);
		std::cout << getter(item->getName()) << std::endl;
	}
}

void Inventory::removeItem(string itemName, int value)
{
	int count = 0;
	vector<Item*>::iterator it;

	setter(itemName, value);
	
	if (getter(itemName) == 0)
	{
		for (it = playerInventory.begin(); it != playerInventory.end(); it++)
		{
			if ((*it)->getName() == itemName)
			{
				break;
			}
			count++;
		}

		playerInventory.erase(playerInventory.begin() + count);
	}
} 

bool Inventory::ItemExistsInInventory(string itemName)
{
	if (getter(itemName) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


