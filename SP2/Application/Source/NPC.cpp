#include "NPC.h"

int NPC::hPrice = 10;
int NPC::sPrice = 10;
int NPC::tPrice = 10;

NPC::NPC()
{
	//Currency::get_instance()->value_adder(1000);		//test
	//Currency::get_instance()->add_mineral("iron");
	menu = new Func_AABB(Vector3(1082, 625, 0), Vector3(1347, 900, 0));	//hull
	crafting.push_back(menu);
	menu = new Func_AABB(Vector3(1082, 320, 0), Vector3(1347, 591, 0));
	crafting.push_back(menu);
	menu = new Func_AABB(Vector3(1081, 0, 0), Vector3(1347, 282, 0));
	crafting.push_back(menu);

	menu = new Func_AABB(Vector3(933, 268, 0), Vector3(1587, 330, 0));
	selling.push_back(menu);
	menu = new Func_AABB(Vector3(933, 182, 0), Vector3(1587, 242, 0));
	selling.push_back(menu);
	menu = new Func_AABB(Vector3(933, 97, 0), Vector3(1587, 159, 0));
	selling.push_back(menu);
	menu = new Func_AABB(Vector3(933, 14, 0), Vector3(1587, 75, 0));
	selling.push_back(menu);
}

NPC::~NPC()
{

}

void NPC::sell(Vector3 mPos)
{
	int money = Currency::get_instance()->value_getter();
	//sell minerals for money;
	static bool press = false;
	if (Application::IsKeyPressed(VK_LBUTTON) && press == false)
	{
		press = true;
		for (int i = 0; i < selling.size(); i++)
		{
			if (selling[i]->mouseInAABB(mPos))
			{
				if (i == 0)
				{
					if (Currency::get_instance()->get_mineral("iron") > 0)
					{
							Currency::get_instance()->set_mineral("iron");
							money += 1;
					}
				}
				else if (i == 1)
				{
					if (Currency::get_instance()->get_mineral("titanium") > 0)
					{
						Currency::get_instance()->set_mineral("titanium");
						money += 2;
					}
				}
				else if (i == 2)
				{
					if (Currency::get_instance()->get_mineral("mithril") > 0)
					{
						Currency::get_instance()->set_mineral("mithril");
						money += 3;
					}
				}
				else if (i == 3)
				{
					if (Currency::get_instance()->get_mineral("bismuth") > 0)
					{
						Currency::get_instance()->set_mineral("bismuth");
						money += 4;
					}
				}
				Currency::get_instance()->value_setter(money);
			}
		}
	}
	else if (!Application::IsKeyPressed(VK_LBUTTON))
	{
		press = false;
	}
}

void NPC::craft(Vector3 mPos)
{
	int money = Currency::get_instance()->value_getter();
	StudioProject::Player->fullHealth();

	static bool press = false;

	if (Application::IsKeyPressed(VK_LBUTTON) && press == false)
	{
		press = true;
		for (int i = 0; i < crafting.size(); i++)
		{
			if (crafting[i]->mouseInAABB(mPos))
			{
				if (i == 0)
				{
					if (Currency::get_instance()->value_getter() > hPrice)
					{
						int temp = StudioProject::Player->hull->getHullPoint();	//find current hp
						StudioProject::Player->hull->setHP(temp + 10);			//increase hp by 10
						StudioProject::Player->fullHealth();
						money -= hPrice;
						hPrice += 10;
						Currency::get_instance()->value_setter(money);
						//std::cout << StudioProject::Player->getHP() << std::endl;
					}
				}
				else if (i == 1)
				{
					if (Currency::get_instance()->value_getter() > sPrice)
					{
						int temp = StudioProject::Player->shield->getShieldPoint();	//find current hp
						StudioProject::Player->shield->setSP(temp + 10);			//increase hp by 10
						money -= sPrice;
						sPrice += 10;
						Currency::get_instance()->value_setter(money);
					}
				}
				else if (i == 2)
				{
					if (Currency::get_instance()->value_getter() > tPrice)
					{
						int temp = StudioProject::Player->thruster->getThrust();	//find current hp
						StudioProject::Player->thruster->setThrust(temp + 2);			//increase hp by 10
						money -= tPrice;
						tPrice += 10;
						Currency::get_instance()->value_setter(money);
					}
				}
			}
		}
	}
	if (!Application::IsKeyPressed(VK_LBUTTON))
	{
		press = false;
	}
}