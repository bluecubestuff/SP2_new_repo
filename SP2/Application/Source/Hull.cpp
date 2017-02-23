#include "Hull.h"

int Hull::count = 0;

Hull::Hull()
{
	Hull::count++;
	this->ID = "H" + std::to_string(Hull::count);		//update the ID

	int temp = hue.generate_range(0, 3);
	float temptemp = hue.generate_range(0, 3);
	string type[4] = { "D", "C", "B", "A" };
	string grade[4] = { "4", "3", "2", "1" };
	this->type = type[temp] + grade[(int)temptemp];

	std::cout << temp << ' ' << temptemp << std::endl;
	
	temp += 1; temptemp += 1;
	int temptemptemp = hue.generate_range(temp * 100 + (temptemp - 1) * 25, temp * 100 + temptemp * 25);
	this->hullPoint = temptemptemp;

	int temptemptemptemp = hue.generate_range(temp * 10 + (temptemp - 1) * 2.5, temp * 10 + temptemp * 2.5);
	this->mass = temptemptemptemp;
	
	this->name = "kitson is slimjim"; // place holder
}

Hull::Hull(int hp, float m, string ID, string name, string type)
{
	this->hullPoint = hp;
	this->mass = m;
	this->ID = ID;
	this->name = name;
	this->type = type;
}

Hull::~Hull()
{

}

int Hull::getHullPoint()
{
	return hullPoint;
}

int Hull::getMass()
{
	return mass;
}