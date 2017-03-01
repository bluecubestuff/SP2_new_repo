#include "NPC.h"

int NPC::hPrice = 10;
int NPC::sPrice = 10;
int NPC::tPrice = 10;

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
	//placeholder
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
	static bool press = false;
	if (Application::IsKeyPressed('1') && press == false)
	{
		if (Currency::get_instance()->value_getter() > hPrice)
		{
			press = true;
			if (StudioProject::Player->getHP() < 200)
			{
				int temp = StudioProject::Player->hull->getHullPoint();	//find current hp
				StudioProject::Player->hull->setHP(temp + 10);			//increase hp by 10
				StudioProject::Player->fullHealth();
				//StudioProject::IronValue -= 40;
				money -= hPrice;
				hPrice += 10;
				Currency::get_instance()->value_setter(money);
				//std::cout << StudioProject::Player->getHP() << std::endl;
			}
		}
		//upgrade hull
		//spend money
		//use resources
	}
	if (Application::IsKeyPressed('2') && press == false)
	{
		press = true;
		if (Currency::get_instance()->value_getter() > sPrice)
		{
			if (StudioProject::Player->shield->getShieldPoint())
			{
				int temp = StudioProject::Player->shield->getShieldPoint();	//find current hp
				StudioProject::Player->shield->setSP(temp + 10);			//increase hp by 10
				//StudioProject::Player->fullHealth();
				//StudioProject::IronValue -= 40;
				money -= sPrice;
				sPrice += 10;
				Currency::get_instance()->value_setter(money);
				//std::cout << StudioProject::Player->getHP() << std::endl;
			}
		}
		//upgrade shield
	}
	if (Application::IsKeyPressed('3') && press == false)
	{
		press = true;
		if (Currency::get_instance()->value_getter() > tPrice)
		{
			if (StudioProject::Player->getThrust() < 20)
			{
				int temp = StudioProject::Player->thruster->getThrust();	//find current hp
				StudioProject::Player->thruster->setThrust(temp + 1);			//increase hp by 10
				//StudioProject::Player->fullHealth();
				//StudioProject::IronValue -= 40;
				money -= tPrice;
				tPrice += 10;
				Currency::get_instance()->value_setter(money);
				//std::cout << StudioProject::Player->getHP() << std::endl;
			}
		}
		//upgrade thrusters
	}
	if (!Application::IsKeyPressed('1') && !Application::IsKeyPressed('2') && Application::IsKeyPressed('3'))
	{
		press = false;
	}
}