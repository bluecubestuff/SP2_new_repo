#include "landEntity.h"

Vector3 LandEntity::getter(std::string something)
{
	if (something == "forward")
	{
		return this->Forward;
	}
	else if (something == "right")
	{
		return this->Right;
	}
	else if (something == "up")
	{
		return this->Up;
	}
	else if (something == "position")
	{
		return this->Position;
	}
	else
	{
		return NULL;
	}
}

Vector3 LandEntity::getRight()
{
	return this->Right;
}

float LandEntity::getHealth()
{
	return this->Health;
}

void LandEntity::setHealth(float newHP)
{
	this->Health = newHP;
}

void LandEntity::modifyHealth(std::string modifier, float value)
{
	if (modifier == "increase")
	{
		this->Health = this->Health + value;
	}
	else if (modifier == "decrease")
	{
		this->Health = this->Health - value;
	}
}

float LandEntity::getShield()
{
	return this->Shield;
}

void LandEntity::setShield(float newS)
{
	this->Shield = newS;
}

void LandEntity::modifyShield(std::string modifier, float value)
{
	if (modifier == "increase")
	{
		this->Shield = this->Shield + value;
	}
	else if (modifier == "decrease")
	{
		this->Shield = this->Shield - value;
	}
}