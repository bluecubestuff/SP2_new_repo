#include "ItemFactory.h"
#include "MyMath.h"


ItemFactory::ItemFactory() {}

ItemFactory::~ItemFactory()
{
	delete this;
}

ItemFactory* ItemFactory::get_instance()
{
	if (!instance)
	{
		instance = new ItemFactory;
	}
	return instance;
}

void ItemFactory::randomlyCreateWeapon()
{
	std::string weaponName[3] = {"gungun","saber","rocket"};
	int stringID, value, damage, durability;

	stringID = Math::RandIntMinMax(0, 2);
	value = Math::RandIntMinMax(10, 1000);
	durability = Math::RandIntMinMax(50, 200);
	damage = Math::RandIntMinMax(value / 4, value / 2);
	

	WeaponStorage.push_back(new Weapon(weaponName[stringID], value, durability, damage));
}

void ItemFactory::createWeapon(Weapon* weapon)
{
	WeaponStorage.push_back(weapon);
}

vector<Weapon*> ItemFactory::weapon_storage_getter()
{
	return WeaponStorage;
}