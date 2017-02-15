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
}

EnemyShip::~EnemyShip()
{
	//delete this;
}

void EnemyShip::Update(double dt, Vector3 playerPos, Vector3 playerFor)
{
	float rotateSpeed = turnSpeed * dt;
	Vector3 target = playerPos - this->Position;
	if (this->Forward != target.Normalized())
	{
		//float angleOfDisplacement = Math::DegreeToRadian(acos((this->Forward.Dot(target.Normalized()) / (this->Forward.Length() * target.Normalized().Length()))));
		Vector3 temp = this->Forward.Cross(target.Normalized());
		temp.Normalize();
		Mtx44 rotate;
		rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);
		this->Forward = rotate * this->Forward;
		this->Right = rotate * this->Right;
		this->Up = rotate * this->Up;
	}
	this->Position += this->Forward * dt * 8;
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}