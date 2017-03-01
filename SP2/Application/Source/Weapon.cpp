#include "Weapon.h"

Weapon::Weapon(string wName, unsigned value, int wDurability, unsigned dmg) : Item(wName, value, wDurability), weaponDamage(dmg)
{

}

Weapon::~Weapon() {}

unsigned Weapon::getWeaponDamage()
{
	return weaponDamage;
}

//void Weapon::generateWeapon(unsigned numOfWeapon)
//{
//	for (unsigned i = 0; i < numOfWeapon; ++i)
//	{
//		//this->WeaponDataBase[weaponID] = new Weapon("string", 1, 1, 1); //place holder
//		//this->weaponID++;
//	}
//}

//void Weapon::add_weapon_to_data_base(Weapon* aWeapon)
//{
//	//this->WeaponDataBase[weaponID] = aWeapon;
//	//weaponID++;
//}

//void Weapon::add_item_to()
//{
//}

//Weapon* Weapon::getWeapon(unsigned ID)
//{
//	return WeaponDataBase[ID];
//}