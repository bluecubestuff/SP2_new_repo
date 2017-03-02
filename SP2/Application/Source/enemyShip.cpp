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
	this->attack = false;
	this->fireRate = 0;

	hull = new Hull;
	this->hullPoints = hull->getHullPoint();;
	this->mass = hull->getMass();

	shield = new Shield;
	shieldPoints = shield->getShieldPoint();
	//this->maxShield = shield->getShieldPoint();

	thruster = new Thruster;
	this->thrust = thruster->getThrust();
	this->turnSpeed = (thrust / mass);

	reactor = new PowerPlant;
	this->power = reactor->getPower();
	this->speed = (thrust / sqrt(mass)) * 2;

	this->hitbox = new Func_AABB;
	this->hitbox->updateAABB(size, size, size, this->Position);

	

	/*if (Math::RandIntMinMax(0, 1))
	{
		AI = AI::PASSIVE;
	}
	else
	{
		AI = AI::AGRESSIVE;
	}*/
	AI = AI::PASSIVE;
}

EnemyShip::~EnemyShip()
{
	//delete this;
}

void EnemyShip::Update(double dt, Vector3 playerPos, Vector3 playerFor)
{
	switch (AI)
	{
	case AI::PASSIVE:
		switch (Passive)
		{
		case PIDLE:
			//std::cout << "Idle" << std::endl;
			idle(dt);
			break;
		case PCHASE:
			//std::cout << "Chase" << std::endl;
			chase(dt, playerPos);
			break;
		case PATTACK:
			attack = true;
			std::cout << "Attack" << std::endl;
			break;
		case PBREAKOFF:
			breakoff(dt, playerPos);
			//std::cout << "Breakoff" << std::endl;
			break;
		default:
			break;
		}
		break;
	case AI::AGRESSIVE:
		switch (Agressive)
		{
		case AIDLE:
			break;
		case ACHASE:
			break;
		case AATTACK:
			break;
		case ABREAKOFF:
			break;
		default:
			break;
		}
		break;
	}

	Vector3 target = playerPos - this->Position;
	float distance = target.Length();
	//std::cout << distance << std::endl;

	float angle = Math::RadianToDegree(acos((target.Normalized()).Dot(this->Forward.Normalized())));
	if (angle < 3 && angle > -3)
	{
		//Passive = PATTACK;
		//this->Forward = target.Normalized();
		this->attack = true;
	}
	else
	{
		this->attack = false;
	}
	//std::cout << angle << std::endl;

	if (distance > 400 && agro != true)
	{
		Passive = PIDLE;
	}
	else if (distance <= 50)
	{
		Passive = PBREAKOFF;
	}
	else if ((distance <= 400 && distance > 50 || agro == true) && Passive != PBREAKOFF)	//if player is 100 to 400 units away, or if the enemy was hit by player, and they must not be doing a breakoff
	{
		Passive = PCHASE;
	}

	//std::cout << Position << "thrsut" << std::endl;
	//std::cout << distance << std::endl;
	hitbox->updateAABB(size, size, size, this->Position);	//update the aabb of the enemy
	fireRate += dt;

	Up = Right.Cross(Forward);
	Up.Normalize();

	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, -this->Up.x, -this->Up.y, -this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}

void EnemyShip::chase(double dt, Vector3 playerPos)
{
	this->Position += this->Forward * dt * this->speed;		//always translate the enemy
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
		//Passive = PATTACK;
		this->Forward = target.Normalized();
	}
}

void EnemyShip::idle(double dt)
{
	this->Position += this->Forward * dt * 5;
	Mtx44 rotation;
	rotation.SetToRotation(10 * dt, 0, 1, 0);
	this->Forward = rotation * this->Forward;
	this->Right = rotation * this->Right;
	this->Up = this->Right.Cross(this->Forward);
	this->Up.Normalize();
}

void EnemyShip::breakoff(double dt, Vector3 playerPos)
{
	float distance = (playerPos - this->Position).Length();
	Vector3 target = playerPos - this->Position;
	Vector3 temp;

	this->Position += this->Forward * dt * this->speed * 1.5;		//always translate the enemy
	static float totalTurn = 0;
	float rotateSpeed = 30.f * dt;

	try
	{
		temp = target.Cross(this->Forward);
	}
	catch (std::exception &e)
	{
		temp = this->Right;
	}
	temp.Normalize();
	
	Mtx44 rotation;
	rotation.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);
	if (totalTurn < 180)
	{
		Forward = rotation * Forward;
		Right = rotation * Right;
		Up = rotation * Up;
	}

	if (distance > 75)
	{
		totalTurn = 0;
		Passive = PCHASE;
	}
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