#include "Thruster.h"

int Thruster::count = 0;



Thruster::Thruster()
{
	Thruster::count++;
	this->ID = "T" + std::to_string(Thruster::count);		//update the ID

	int temp = hue.generate_range(0, 3);
	float temptemp = hue.generate_range(0, 3);

	//std::cout << temp << ' ' << temptemp << std::endl;
	string type[4] = { "D", "C", "B", "A" };
	string grade[4] = { "4", "3", "2", "1" };
	this->type = type[temp] + grade[(int)temptemp];

	temp += 1; temptemp += 1;
	int temptemptemp = hue.generate_range(temp * 10 + (temptemp - 1) * 2.5, temp * 10 + temptemp * 2.5);
	this->thrust = temptemptemp;

	float temptemptemptemp = hue.generate_range(temp * 25 + (temptemp - 1) * 6.25, temp * 25 + temptemp * 6.25);
	this->powerDraw = temptemptemptemp;

	this->name = "kitson is meanbean"; // place holder
}

Thruster::Thruster(int thrust, float powerDraw, string ID, string name, string type)
{
	this->thrust = thrust;
	this->powerDraw = powerDraw;
	this->ID = ID;
	this->name = name;
	this->type = type;
}

Thruster::~Thruster()
{

}

int Thruster::getThrust()
{
	return this->thrust;
}

float Thruster::getPowerDraw()
{
	return this->powerDraw;
}