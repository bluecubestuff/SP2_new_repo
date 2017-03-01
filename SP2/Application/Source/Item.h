#ifndef _ITEM_H
#define _ITEM_H

#include <map>
using std::map;

#include <string>
using std::string;

class Item
{
public:
	Item(string, unsigned,int);
	virtual ~Item();

	unsigned getValue();
	int getDurability();
	string getName();

private:

	string itemName;
	unsigned itemValue;
	int itemDurability;
};

#endif