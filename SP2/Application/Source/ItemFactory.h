#ifndef _ITEM_FACTORY_H
#define _ITEM_FACTORY_H

#include "Weapon.h"

#include <string>
#include <vector>
using std::vector;

class ItemFactory
{
public:

	~ItemFactory();

	void randomlyCreateWeapon();
	void createWeapon(Weapon*);

	vector<Weapon*> weapon_storage_getter();

	static ItemFactory* get_instance();
	

private:

	ItemFactory();
	vector<Weapon*> WeaponStorage;
	static ItemFactory* instance;
};


#endif