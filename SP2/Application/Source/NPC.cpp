#include "NPC.h"

NPC::NPC()
{
	StudioProject::Player->fullHealth();
	//Currency::get_instance()->value_adder(500);
}

NPC::~NPC()
{

}

void NPC::sell()
{
	int money = Currency::get_instance()->value_getter();
	//sell minerals for money;
	if (StudioProject::IronValue > 0)
	{
		if (Application::IsKeyPressed('1'))
		{
			StudioProject::IronValue -= 1;
			money += 1;
		}
	}
	if (StudioProject::TitaniumValue > 0)
	if (Application::IsKeyPressed('2'))
	{
		StudioProject::TitaniumValue -= 1;
		money += 2;
	}
	if (StudioProject::MithrilValue > 0)
	if (Application::IsKeyPressed('3'))
	{
		StudioProject::MithrilValue -= 1;
		money += 3;
	}
	if (StudioProject::BismuthValue > 0)
	if (Application::IsKeyPressed('4'))
	{
		StudioProject::BismuthValue -= 1;
		money += 4;
	}

	if (money > 0)
	{
		if (Application::IsKeyPressed('5'))
		{
			StudioProject::IronValue += 1;
			money -= 1;
		}
	}
	if (money > 1)
	{
		if (Application::IsKeyPressed('6'))
		{
			StudioProject::TitaniumValue += 1;
			money -= 2;
		}
	}
	if (money > 2)
	{
		if (Application::IsKeyPressed('7'))
		{
			StudioProject::MithrilValue += 1;
			money -= 3;
		}
	}
	if (money > 3)
	{
		if (Application::IsKeyPressed('8'))
		{
			StudioProject::BismuthValue += 1;
			money -= 4;
		}
	}
	Currency::get_instance()->value_setter(money);
}

void NPC::craft()
{
	int money = Currency::get_instance()->value_getter();
	//needa do if click on iron and such
	if (Application::IsKeyPressed('1'))
	{
		if (Currency::get_instance()->value_getter() > 20)
		{
			int temp = StudioProject::Player->hull->getHullPoint();	//find current hp
			StudioProject::Player->hull->setHP(temp + 10);			//increase hp by 10
			StudioProject::Player->fullHealth();
			//StudioProject::IronValue -= 40;
			money -= 20;
			Currency::get_instance()->value_setter(money);
			//std::cout << StudioProject::Player->getHP() << std::endl;
		}
		//upgrade hull
		//spend money
		//use resources
	}
	if (Application::IsKeyPressed('2'))
	{
		//upgrade shield
	}
	if (Application::IsKeyPressed('3'))
	{
		//upgrade thrusters
	}
}