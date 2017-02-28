#include "Inventory.h"

using std::to_string;


Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

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