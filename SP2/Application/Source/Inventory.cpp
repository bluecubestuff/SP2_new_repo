#include "Inventory.h"

<<<<<<< HEAD
using std::to_string;


Inventory::Inventory()
{

=======
Inventory::Inventory()
{
	inventoryOpen = false;
	amountOfBismuth = 0;
	amountOfIron = 0;
	amountOfMithril = 0;
	amountOfTitanium = 0;
	posY = 17;
>>>>>>> 3956454f5ff70878ddd79c712349ab835ccc6b62
}

Inventory::~Inventory()
{

}

<<<<<<< HEAD
void Inventory::AddingStuff()
{
	
	string irontext = "Iron";
	string titaniumtext = "Titanium";
	string mithriltext = "Mithril";
	string bismuthtext = "Bismuth";

	if (_Iron > 0)
	{
		myscene->Iron = true;
	}
	if (_Titanium > 0)
	{
		inventory.push_back(titaniumtext);
		inventory.push_back(to_string(_Titanium));
	}
	if (_Mithril > 0)
	{
		inventory.push_back(mithriltext);
		inventory.push_back(to_string(_Mithril));
	}
	if (_Bismuth > 0)
	{
		inventory.push_back(bismuthtext);
		inventory.push_back(to_string(_Bismuth));
	}
}
//void StudioProject::RenderInventory()
//{
//	for (int i = 0; 1 < myinventory->inventory.size(); i++)
//	{
//		if (myinventory->inventory[i] == "Iron")
//		{
//			Iron = true;
//			IronValue = myinventory->inventory[(i + 1)];
//		}
//		if (myinventory->inventory[i] == "Titanium")
//		{
//			Titanium = true;
//			TitaniumValue = myinventory->inventory[(i + 1)];
//		}
//		if (myinventory->inventory[i] == "Mithril")
//		{
//			Mithril = true;
//			MithrilValue = myinventory->inventory[(i + 1)];
//		}
//
//		if (myinventory->inventory[i] == "Bismuth")
//		{
//			Bismuth = true;
//			BismuthValue = myinventory->inventory[(i + 1)];
//		}
//	}
//
//}
=======
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


>>>>>>> 3956454f5ff70878ddd79c712349ab835ccc6b62
