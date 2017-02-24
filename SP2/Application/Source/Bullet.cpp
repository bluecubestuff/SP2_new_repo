#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(Vector3 p, Vector3 f, Vector3 u, Vector3 r)
{
	this->Position = p;
	this->Forward = f;
	this->Up = u;
	this->Right = r;
	this->distance = Vector3(0, 0, 0);
	this->outOfRange = false;
	this->Stamp = Mtx44(r.x, r.y, r.z, 0, u.x, u.y, u.z, 0, f.x, f.y, f.z, 0, p.x, p.y, p.z, 1);
}

Bullet::~Bullet()
{

}

void Bullet::Update(double dt)
{
	this->Position += Forward * dt * 150;
	this->distance += Forward * dt * 150;
	if (distance.Length() > 500)
	{
		outOfRange = true;
	}
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

Mtx44 Bullet::getMatrix()
{
	return this->Stamp;
}