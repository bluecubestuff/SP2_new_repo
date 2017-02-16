#include "enemyShip.h"

EnemyShip::EnemyShip()
{

}

EnemyShip::EnemyShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, float s)
{
	this->Forward = f;
	this->Up = u;
	this->Right = r;
	this->Position = p;
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
	this->turnSpeed = s;
	this->locked = false;		//if enemy has been locked on by player
}

EnemyShip::~EnemyShip()
{
	//delete this;
}

void EnemyShip::Update(double dt, Vector3 playerPos, Vector3 playerFor)
{
	float rotateSpeed = turnSpeed * dt;			//set rotation speed
	Vector3 target = playerPos - this->Position;	//get the target vector
	if (this->Forward != target.Normalized())		//if the enemy is not facing the plaayer
	{
		Vector3 temp = this->Forward.Cross(target.Normalized());		//cross forward and target to get the vector of rotation
		temp.Normalize();
		Mtx44 rotate;
		rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);		//rotate the enemy enemy ship at a speed to face the player
		this->Forward = rotate * this->Forward;
		this->Right = rotate * this->Right;
		this->Up = rotate * this->Up;
	}
	this->Position += this->Forward * dt * 8;		//enemy will always move 8 units/s
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}