#include "Missile.h"

Missile::Missile()
{

}

Missile::Missile(EnemyShip e, PlayerShip me, float s, bool fire)
{
	this->e = e;
	this->me = me;
	this->fire = fire;
	this->turnSpeed = s;
	if (fire)
	{
		this->Position = this->me.getter("position");
		this->Forward = this->me.getter("forward");
		this->Right = this->me.getter("right");
		this->Up = this->me.getter("up");
	}
	else
	{
		this->Position = this->e.getter("position");
		this->Forward = this->e.getter("forward");
		this->Right = this->e.getter("right");
		this->Up = this->e.getter("up");
	}
}

Missile::~Missile()
{
	delete this;
}

void Missile::tracking(double dt, Vector3 p)
{
	float rotateSpeed = turnSpeed;
	if (this->fire)		//if player shoot missile
	{
		Vector3 target = (p - this->Position);
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
		this->Position += this->Forward * 100 * dt;
		this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
	}
	else
	{				//if enemy shoot missile
		Vector3 target = p - this->Position;
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
		this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
	}
}