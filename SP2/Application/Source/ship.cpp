#include "ship.h"

Ship::Ship()
{
	Forward = Vector3(0, 0, 1);
	Up = Vector3(0, 1, 0);
	Right = Vector3(1, 0, 0);
	Position = Vector3(0, 0, 0);
	Inertia = Vector3(0, 0, 0);

	locked = false;
	hit = false;

	Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

Ship::Ship(Vector3 f, Vector3 u, Vector3 r, Vector3 p, Vector3 i, float s)
{
	Forward = f;
	Up = u;
	Right = r;
	Position = p;
	Inertia = i;

	locked = false;
	hit = false;

	Stamp = Mtx44(r.x, r.y, r.z, 0, u.x, u.y, u.z, 0, f.x, f.y, f.z, 0, p.x, p.y, p.z, 1);
}

Ship::~Ship()
{

}

Vector3 Ship::getter(std::string something)
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
	else if (something == "locked")
	{
		return this->locked;
	}
	else
	{
		return NULL;
	}
}

Mtx44 Ship::getStamp()
{
	return this->Stamp;
}

Func_AABB* Ship::getAABB()
{
	return hitbox;
}

void Ship::setHit()
{
	if (this->hit == false)
		this->hit = true;
	else
		this->hit = false;
}

bool Ship::getHit()
{
	return hit;
}

float Ship::getSize()
{
	return this->size;
}

void Ship::decreaseHealth(float dadsad)
{
	hullPoints -= dadsad;
}

float Ship::getHP()
{
	return hullPoints;
}

void Ship::fullHealth()
{
	hullPoints = hull->getHullPoint();
}

void Ship::setHP(float h)
{
	hull->setHP(h);
}

void Ship::shieldUpdate(double dt)
{
	if (shieldPoints != shield->getShieldPoint())
	{
		offTime += dt;
		if (offTime > 5)
		{
			if (shieldPoints < shield->getShieldPoint())
			{
				shieldPoints += dt * 20;
			}
		}
		if (getHit())
		{
			offTime = 0;
		}
	}
}

void Ship::decreaseShield(float adasd)
{
	shieldPoints -= adasd;
}

float Ship::getSP()
{
	return shieldPoints;
}

float Ship::getFullSP()
{
	return shield->getShieldPoint();
}

void Ship::setSP(float s)
{
	shield->setSP(s);
}

int Ship::getThrust()
{
	return thruster->getThrust();
}

void Ship::setThrust(float t)
{
	thruster->setThrust(t);
}