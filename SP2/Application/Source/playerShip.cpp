#include "PlayerShip.h"

static float l = 0;

PlayerShip::PlayerShip()
{
	this->Forward = Vector3(0, 0, 1);
	this->Up = Vector3(0, 1, 0);
	this->Right = Vector3(1, 0, 0);
	this->Position = Vector3(500, 500, 500);
	this->Inertia = Vector3(0, 0, 0);
	this->Speed = 0;
	this->camTime = 0.f;

	Camera = new Camera2;
	Camera->Init(this->Position, this->Forward, this->Up);
	ThirdCamera = new Camera3;

	this->FlightAssist = true;
	this->freeCam = false;
	this->firstThird = true;
	this->changeCam = false;

	this->size = 1;
	hull = new Hull(100, 10.f, "BASE_H", "Second Hand Hull", "D4");
	this->hullPoints = hull->getHullPoint();;
	this->mass = hull->getMass();
	
	shield = new Shield(100, 50.f, "BASE_S", "Second Hand Shield Generator", "D4");
	this->maxShield = shield->getShieldPoint();

	thruster = new Thruster(10.f, 25.f, "BASE_T", "Second Hand Thruster", "D4");
	this->thrust = thruster->getThrust();
	this->turnSpeed = thrust / mass;

	reactor = new PowerPlant(100.f, "BASE_R", "second Hand Reactor", "D4");
	this->power = reactor->getPower();

	hit = false;

	//std::cout << thrust << std::endl << mass << std::endl;

	hitbox = new Func_AABB;
	hitbox->updateAABB(size, size, size, this->Position);
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

PlayerShip::PlayerShip(Vector3 f, Vector3 u, Vector3 r, Vector3 p, Vector3 i, float s)
{
	this->Forward = f;
	this->Up = u;
	this->Right = r;
	this->Position = p;
	this->Inertia = i;

	Camera = new Camera2;
	Camera->Init(this->Position, this->Forward, this->Up);
	ThirdCamera = new Camera3;

	this->FlightAssist = true;
	this->freeCam = false;
	this->firstThird = true;
	this->changeCam = false;
	this->hit = false;

	this->Stamp = Mtx44(r.x, r.y, r.z, 0, u.x, u.y, u.z, 0, f.x, f.y, f.z, 0, p.x, p.y, p.z, 1);
}

PlayerShip::~PlayerShip()
{
	//delete Camera;
	//delete ThirdCamera;
	//delete this;
}

void PlayerShip::locking(EnemyShip* target, double dt)
{
	//do point to aabb to enemyship, if stays for 3s, locked enabled
	if (l >= 3)
	{
		target->locked = true;
	}
	if (target->getTargeted())
	{
		l += dt;
	}
	else if (!target->getTargeted())
	{
		target->locked = false;
	}
	else
		l = 0;
	//std::cout << l << std::endl;
}

void PlayerShip::Update(double dt)	//Player PlayerShip movement and control
{
	//========================================================================
	//Setting FlightAssist on or off
	if (Application::IsKeyPressed('X'))
	{
		FlightAssist = false;
	}
	if (Application::IsKeyPressed('Z'))
	{
		FlightAssist = true;
	}
	//========================================================================
	//toggle between mouse control the camera or the ship
	if (Application::IsKeyPressed(VK_MBUTTON) && freeCam)
	{
		if (camTime < 0)
		{
			freeCam = false;
			this->Camera->Init(this->Position, this->Forward, this->Up);
			camTime = 0.5f;
		}
		camTime -= dt;
	}
	else if (Application::IsKeyPressed(VK_MBUTTON) && !freeCam)
	{
		if (camTime < 0)
		{
			freeCam = true;
			this->Camera->Init(this->Position, this->Forward, this->Up);
			camTime = 0.5f;
		}
		camTime -= dt;
	}
	//========================================================================
	if (Application::IsKeyPressed(VK_RETURN))
	{
		firstThird = false;
		changeCam = true;
	}
	else if (Application::IsKeyPressed(VK_RSHIFT))
	{
		firstThird = true;
		changeCam = true;
	}
	//========================================================================
	if (this->FlightAssist == false)	//FLIGHT ASSISTS OFF
	{
		//Adjusting how fast the player want to fly
		//====================================================================
		if (Application::IsKeyPressed('W') && this->Speed < 10.f)
		{
			this->Speed += 4.f * (float)dt;
		}
		else if (Application::IsKeyPressed('S') && this->Speed > -10.f)
		{
			this->Speed += -4.f * (float)dt;
		}
		//Setting Velocity to zero
		else if (Application::IsKeyPressed('0'))
		{
			this->Speed = 0;
		}
		//=====================================================================
		if (this->Speed > 0)
		{
			if (this->Inertia.Length() < this->Speed * 2)	//if PlayerShip Velocity is lower than speed
				this->Inertia += this->Forward * (float)dt * 4.f;	//increase PlayerShip velocity
		}
		else if (this->Speed < 0)
		{
			if (this->Inertia.Length() > this->Speed)
				this->Inertia -= this->Forward * (float)dt;	//increase PlayerShip Velocity
		}
		//======================================================================
		if (Application::IsKeyPressed('E') && Inertia.Length() < 5)	//strafe right
		{
			this->Position -= this->Right.Normalized() * (float)dt;
		}
		else if (Application::IsKeyPressed('Q') && Inertia.Length() < 5)	//strafe left
		{
			this->Position += this->Right.Normalized() * (float)dt;
		}
		//======================================================================
		if (Application::IsKeyPressed('R'))		//elevate
		{
			this->Position += this->Up.Normalized() * (float)dt;
		}
		else if (Application::IsKeyPressed('F'))	//depress
		{
			this->Position -= this->Up.Normalized() * (float)dt;
		}
		if (Application::IsKeyPressed('D'))		//roll right
		{
			float rollSpeed = 30 * (float)dt;
			Mtx44 roll;
			roll.SetToRotation(rollSpeed, this->Forward.x, this->Forward.y, this->Forward.z);
			this->Right = roll * this->Right;
			this->Up = roll * this->Up;
		}
		else if (Application::IsKeyPressed('A'))		//roll left
		{
			float rollSpeed = -30 * (float)dt;
			Mtx44 roll;
			roll.SetToRotation(rollSpeed, this->Forward.x, this->Forward.y, this->Forward.z);
			this->Right = roll * this->Right;
			this->Up = roll * this->Up;
		}
		this->Position += this->Inertia * (float)dt;	//update position according to PlayerShip inertia
	}
	//===========================================================================
	else if (this->FlightAssist == true)	//FLIGHT ASSISTS ON
	{
		this->Inertia = this->Forward * Speed * 2.f;
		if (Application::IsKeyPressed('W') && this->Speed < 10.f)
		{
			this->Speed += 4.f * (float)dt;
		}
		else if (Application::IsKeyPressed('S') && this->Speed > -10.f)
		{
			this->Speed += -4.f * (float)dt;
		}
		if (Application::IsKeyPressed('E'))	//strafe right
		{
			this->Position -= this->Right.Normalized() * (float)dt;
		}
		else if (Application::IsKeyPressed('Q'))	//strafe left
		{
			this->Position += this->Right.Normalized() * (float)dt;
		}
		//======================================================================
		if (Application::IsKeyPressed('R'))		//elevate
		{
			this->Position += this->Up.Normalized() * (float)dt;
		}
		else if (Application::IsKeyPressed('F'))	//depress
		{
			this->Position -= this->Up.Normalized() * (float)dt;
		}
		if (Application::IsKeyPressed('D'))		//roll right
		{
			float rollSpeed = 30 * (float)dt;
			Mtx44 roll;
			roll.SetToRotation(rollSpeed, this->Forward.x, this->Forward.y, this->Forward.z);
			this->Right = roll * this->Right;
			this->Up = roll * this->Up;
		}
		else if (Application::IsKeyPressed('A'))		//roll left
		{
			float rollSpeed = -30 * (float)dt;
			Mtx44 roll;
			roll.SetToRotation(rollSpeed, this->Forward.x, this->Forward.y, this->Forward.z);
			this->Right = roll * this->Right;
			this->Up = roll * this->Up;
		}
		this->Position += this->Forward * Speed * (float)dt * 2.f;
	}
	//===========================================================================
	//mouse control for the ship
	if (!freeCam && FlightAssist)
	{
		float yawSpeed, pitchSpeed;
		cursorPos = mouse.flightMouse();
		if (Speed > 1 || Speed < -1)
		{
			yawSpeed = cursorPos.x * -(float)dt * turnSpeed / sqrt(abs(Speed));	//if the ship moves faster, the speed of turning decreases
			pitchSpeed = cursorPos.y * (float)dt * turnSpeed / sqrt(abs(Speed));
		}
		else
		{
			yawSpeed = cursorPos.x * -(float)dt * turnSpeed;
			pitchSpeed = cursorPos.y * (float)dt * turnSpeed;
		}
		if (cursorPos.x)
		{
			Mtx44 yaw;
			yaw.SetToRotation(yawSpeed, this->Up.x, this->Up.y, this->Up.z);
			this->Forward = yaw * this->Forward;
			this->Right = yaw * this->Right;
			//this->Up = this->Forward.Cross(this->Right).Normalized();
		}
		if (cursorPos.y)
		{
			Mtx44 pitch;
			pitch.SetToRotation(pitchSpeed, this->Right.x, this->Right.y, this->Right.z);
			//pitch.SetToRotation(pitchSpeed, 1, 0, 0);
			this->Forward = pitch * this->Forward;
			this->Up = pitch * this->Up;
			//this->Right = this->Up.Cross(this->Forward).Normalized();
		}
	}
	else if (!freeCam && !FlightAssist)
	{
		cursorPos = mouse.flightMouse();
		float yawSpeed = cursorPos.x * -(float)dt * turnSpeed;
		float pitchSpeed = cursorPos.y * (float)dt * turnSpeed;
		if (cursorPos.x)
		{			
			Mtx44 yaw;
			yaw.SetToRotation(yawSpeed, this->Up.x, this->Up.y, this->Up.z);
			this->Forward = yaw * this->Forward;
			this->Right = yaw * this->Right;
			//this->Up = this->Forward.Cross(this->Right).Normalized();
		}
		if (cursorPos.y)
		{
			Mtx44 pitch;
			pitch.SetToRotation(pitchSpeed, this->Right.x, this->Right.y, this->Right.z);
			//pitch.SetToRotation(pitchSpeed, 1, 0, 0);
			this->Forward = pitch * this->Forward;
			this->Up = pitch * this->Up;
			//this->Right = this->Up.Cross(this->Forward).Normalized();
		}
	}

	//std::cout << 'x' << cursorPos.x << 'y' << cursorPos.y << std::endl;
	
	//===========================================================================
	if (changeCam)
	{
		if (firstThird)
		{
			Camera->Init(this->Position, this->Forward + this->Position, this->Up);
		}
		else if (!firstThird)
		{
			ThirdCamera->Init(this->Position - this->Forward + this->Up, this->Position, this->Up);
		}
		changeCam = false;
	}
	if (this->firstThird)
	{
		Camera->Update(dt, freeCam, this->Forward, this->Right, this->Up, this->Position);
	}
	else
	{
		ThirdCamera->Update(dt, freeCam, this->Forward, this->Right, this->Up, this->Position);
	}
	//==========================================================================
	//changing targets
	static bool pressing = false;
	static int t = 0;
	if (Application::IsKeyPressed('T') && pressing == false)
	{
		pressing = true;
		std::cout << "t : " << t << " size: " << applicableTargets.size() << std::endl;
		l = 0;
		if (t < applicableTargets.size())
		{
			if (applicableTargets.size() != 0)
			{
				applicableTargets[t]->setTargeted(false);
				applicableTargets[t]->locked = false;
			}
			t++;
			if (t < applicableTargets.size())
			{
				applicableTargets[t]->setTargeted(true);
			}
			else if (t == applicableTargets.size())
			{
				t = 0;
				applicableTargets[t]->setTargeted(true);
			}
			else
				t = 0;
		}
		else
			t = 0;
	}
	else if (!Application::IsKeyPressed('T'))
	{
		pressing = false;
	}
	if (applicableTargets.size() == 0)
	{
		t = 0;
	}
	//==========================================================================
	for (auto &i : applicableTargets)
	{
		if (i->getTargeted())
		{
			locking(i, dt);
		}
		else
		{
			//applicableTargets[t]->locked = false;
		}
	}

	//std::cout << pressing << std::endl;
	//==========================================================================
	//update ship matrix
	this->Stamp = Mtx44(this->Right.x, this->Right.y, this->Right.z, 0, this->Up.x, this->Up.y, this->Up.z, 0, this->Forward.x, this->Forward.y, this->Forward.z, 0, this->Position.x, this->Position.y, this->Position.z, 1);
}

void PlayerShip::withinRange(vector<EnemyShip*> targets)
{
	for (auto &i : targets)
	{
		Vector3 temp = i->getter("position") - this->Position;
		//need to normalize both vectors before doing the acos
		float angle;
		angle = Math::RadianToDegree(acos(temp.Normalized().Dot(this->Forward.Normalized())));
		//if (angle < 20 && angle > -20 && temp.Length() < 300)		//if withing 45 degreess from forward
		//{
		//	if (i->getWithinSights() != true)
		//	{
		//		i->setIGotYouInMySights(true);		//set the bool in enemy to true	
		//		//std::cout << "targeted" << std::endl;
		//		applicableTargets.push_back(i);		//puh back to which targets player can choose
		//		//std::cout << applicableTargets.size() << std::endl;
		//	}
		//}
		//else
		//{
		//	i->setIGotYouInMySights(false);		//else not in ur target list anymore
		//	//std::cout << "untargeted" << std::endl;
		//}
		if (i->getWithinSights() != true)
		{
			i->setIGotYouInMySights(true);		//set the bool in enemy to true	
			//std::cout << "targeted" << std::endl;
			applicableTargets.push_back(i);		//puh back to which targets player can choose
			//std::cout << applicableTargets.size() << std::endl;
		}
	}
	for (int i = 0; i < applicableTargets.size(); i++)
	{
		if (applicableTargets[i]->deaded)
		{
			EnemyShip* temp = applicableTargets[i];
			applicableTargets.erase(applicableTargets.begin() + i);
			delete temp;
		}
		else if (applicableTargets[i]->getWithinSights() == false)		//if is not in within the cone of target
		{
			applicableTargets[i]->setTargeted(false);
			applicableTargets[i]->locked = false;;
			applicableTargets.erase(applicableTargets.begin() + i);			//remove from the vector
			//std::cout << "removed from target list" << std::endl;
			i = 0;
		}
	}
}