#include "PowerPlant.h"

int PowerPlant::count = 0;

PowerPlant::PowerPlant()
{
	PowerPlant::count++;
	this->ID = "P" + std::to_string(PowerPlant::count);		//update the ID

	int temp = hue.generate_range(0, 3);
	float temptemp = hue.generate_range(0, 3);
	string type[4] = { "D", "C", "B", "A" };
	string grade[4] = { "4", "3", "2", "1" };
	this->type = type[temp] + grade[(int)temptemp];

	//std::cout << temp << ' ' << temptemp << std::endl;

	temp += 1; temptemp += 1;
	int temptemptemp = hue.generate_range(temp * 100 + (temptemp - 1) * 25, temp * 100 + temptemp * 25);
	this->power = temptemptemp;

	this->name = "kitson is sir blob blob"; // place holder
}

PowerPlant::PowerPlant(float power, string ID, string name, string type)
{
	this->power = power;
	this->ID = ID;
	this->name = name;
	this->type = type;
}

PowerPlant::~PowerPlant()
{

}

float PowerPlant::getPower()
{
	return power;
}