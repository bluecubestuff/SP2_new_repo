#include "enemyShip.h"

#include <exception>

EnemyShip::EnemyShip()
{

}

EnemyShip::EnemyShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, float t, float size, float speed)
{
	this->Forward = f;
	this->Up = u;
	this->Right = r;
	this->Position = p;
	this->size = size;
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
	this->turnSpeed = t;
	this->locked = false;		//if enemy has been locked on by player
	this->speed = speed;

	this->hitbox = new Func_AABB;
	this->hitbox->updateAABB(size, size, size, this->Position);
}

EnemyShip::~EnemyShip()
{
	//delete this;
}

void EnemyShip::Update(double dt, Vector3 playerPos, Vector3 playerFor)
{
	float rotateSpeed = turnSpeed * dt;
	Vector3 target = playerPos - this->Position;
	try
	{
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
	}
	catch (std::exception& e)
	{
		std::cout << "nothing" << std::endl;
	}

	this->Position += this->Forward * dt * this->speed;
	hitbox->updateAABB(size, size, size, this->Position);

	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}