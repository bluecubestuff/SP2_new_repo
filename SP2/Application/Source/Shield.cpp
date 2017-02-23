#include "Shield.h"

int Shield::count = 0;

Shield::Shield()
{
	Shield::count++;
	this->ID = "S" + std::to_string(Shield::count);		//update the ID

	int temp = hue.generate_range(0, 3);
	float temptemp = hue.generate_range(0, 3);
	string type[4] = { "D", "C", "B", "A" };
	string grade[4] = { "4", "3", "2", "1" };
	this->type = type[temp] + grade[(int)temptemp];

	std::cout << temp << ' ' << temptemp << std::endl;

	temp += 1; temptemp += 1;
	int temptemptemp = hue.generate_range(temp * 100 + (temptemp - 1) * 25, temp * 100 + temptemp * 25);
	this->shieldPoint = temptemptemp;

	float temptemptemptemp = hue.generate_range(temp * 50 + (temptemp - 1) * 12.5, temp * 50 + temptemp * 12.5);
	this->powerDraw = temptemptemptemp;

	this->name = "kitson is snorlax"; // place holder
}

Shield::Shield(int shieldPoint, float powerDraw, string ID, string name, string type)
{
	this->shieldPoint = shieldPoint;
	this->powerDraw = powerDraw;
	this->ID = ID;
	this->name = name;
	this->type = type;
}

Shield::~Shield()
{
	
}

int Shield::getShieldPoint()
{
	return this->shieldPoint;
}

float Shield::getPowerDraw()
{
	return this->powerDraw;
}