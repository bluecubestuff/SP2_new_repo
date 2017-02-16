#include "Missile.h"

Missile::Missile()
{

}

Missile::Missile(EnemyShip* e, PlayerShip* me, float s, bool fire)
{
	this->fire = fire;
	this->turnSpeed = s;
	if (fire)		//set the missile at player if player shot it
	{
		this->Position = me->getter("position");
		this->Forward = me->getter("forward");
		this->Right = me->getter("right");
		this->Up = me->getter("up");
	}
	else
	{
		this->Position = e->getter("position");			//set it at enemy if enemy shot it
		this->Forward = e->getter("forward");
		this->Right = e->getter("right");
		this->Up = e->getter("up");
	}
}

Missile::~Missile()
{
	delete this;
}

void Missile::tracking(double dt, Vector3 p)
{
	float rotateSpeed = turnSpeed * dt;
	Vector3 target = (p - this->Position);			//find my target vector
	if (this->Forward != target.Normalized())
	{
		Vector3 temp = this->Forward.Cross(target.Normalized());
		temp.Normalize();
		Mtx44 rotate;
		rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);
		this->Forward = rotate * this->Forward;
		this->Right = rotate * this->Right;
		this->Up = rotate * this->Up;
	}
	this->Position += this->Forward * 100.f * (float)dt;
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}

void Missile::checkTargets(vector<EnemyShip*> hostiles)
{
	for (auto &i : hostiles)
	{
		if (i->locked)
		{
			this->e = i;			//check if enemy was locked on
		}
	}
}

void Missile::checkTargets(PlayerShip player)
{

}