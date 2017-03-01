#ifndef _WEAPON_H
#define _WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon(string, unsigned, int, unsigned);
	~Weapon();

	unsigned getWeaponDamage();
	//void generateWeapon(unsigned);
	//void add_weapon_to_data_base(Weapon*);
	//Weapon* getWeapon(unsigned);

	//void add_item_to();		//func to add item to player/shop/loots

private:

	unsigned weaponDamage;
	map<unsigned, Weapon*> WeaponDataBase;
	//unsigned weaponID;
};

#endif