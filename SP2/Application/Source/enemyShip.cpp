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
	this->hit = false;
	this->iGotYouInMySights = false;
	this->targeted = false;
	this->deaded = false;

	hull = new Hull;
	this->hullPoints = hull->getHullPoint();;
	this->mass = hull->getMass();

	shield = new Shield;
	this->maxShield = shield->getShieldPoint();

	thruster = new Thruster;
	this->thrust = thruster->getThrust();
	this->turnSpeed = thrust / mass;

	reactor = new PowerPlant;
	this->power = reactor->getPower();

	this->speed = thrust / sqrt(mass);

	this->hitbox = new Func_AABB;
	this->hitbox->updateAABB(size, size, size, this->Position);

	//std::cout << maxShield << std::endl;
	//std::cout << hullPoints << std::endl;
	//std::cout << thrust << std::endl;
	//std::cout << power << std::endl;
}

EnemyShip::~EnemyShip()
{
	//delete this;
}

void EnemyShip::Update(double dt, Vector3 playerPos, Vector3 playerFor)
{
	float rotateSpeed = turnSpeed * 50 * dt;			//set rotation speed
	//std::cout << rotateSpeed << std::endl;
	Vector3 target = playerPos - this->Position;	//the vector between the enemy and player
	try			//in case divide by zero occurs
	{
		if (this->Forward != target.Normalized())		//if the enemy is not facing the enemy
		{
			Vector3 temp = this->Forward.Cross(target.Normalized());		//vector of rotation
			temp.Normalize();
			Mtx44 rotate;
			rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);
			this->Forward = rotate * this->Forward;		//rotate all the enemy matrices
			this->Right = rotate * this->Right;
			this->Up = rotate * this->Up;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Enemy Ship facing Player directly" << std::endl;
	}

	this->Position += this->Forward * dt * this->speed;		//always translate the enemy
	//std::cout << Position << "thrsut" << std::endl;
	hitbox->updateAABB(size, size, size, this->Position);	//update the aabb of the enemy

	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}

bool EnemyShip::getWithinSights()
{
	return iGotYouInMySights;
}

void EnemyShip::setIGotYouInMySights(bool something)
{
	this->iGotYouInMySights = something;
}

bool EnemyShip::getTargeted()
{
	return targeted;
}

void EnemyShip::setTargeted(bool something)
{
	this->targeted = something;
}

float EnemyShip::getSpeed()
{
	return this->speed;
}