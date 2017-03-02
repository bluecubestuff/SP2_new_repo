#include "landPlayer.h"
#include "landEnemy.h"

LandPlayer::LandPlayer()
{
	FPS_CAM = new LandFPSCamera;
}

LandPlayer::LandPlayer(Vector3 pos, Vector3 f, Vector3 r, float health)
{
	FPS_CAM = new LandFPSCamera;
	this->Position = pos;
	this->Forward = f;
	this->Up = Vector3(0, 1, 0);
	this->Right = r;

	this->setHealth(health);
	FPS_CAM->Init(pos, f, this->Up);
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

LandPlayer::~LandPlayer()
{
	delete FPS_CAM;
}

void LandPlayer::Update(double dt)
{
	FPS_CAM->Update(dt, Position, Forward);
	this->Right = (Forward.Cross(Vector3(0, 1, 0))).Normalized();
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

void LandPlayer::Update(double dt, vector<LandEnemy*> landEnemies, vector<LandEnemy*> rangedEnemies)
{
	FPS_CAM->Update(dt, Position, Forward);
	Combat(dt, landEnemies, rangedEnemies);
	this->Right = (Forward.Cross(Vector3(0, 1, 0))).Normalized();
	this->Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
	if (this->Health <= 0)
	{
		std::cout << "You dieded" << std::endl;
	}
}

void LandPlayer::Combat(double dt, vector<LandEnemy*> meleeEnemies, vector<LandEnemy*> rangedEnemies)
{
	if (Application::IsKeyPressed('Q'))
	{
		meleeWeaponEquipped = true;
		rangedWeaponEquipped = false;
		bullets.clear();
	}
	if (Application::IsKeyPressed('E'))
	{
		rangedWeaponEquipped = true;
		meleeWeaponEquipped = false;
		bullets.clear();
	}

	if (meleeWeaponEquipped == true)
	{
		if (Application::IsKeyPressed(VK_LBUTTON))
		{
			for (it = meleeEnemies.begin(); it != meleeEnemies.end(); it++)
			{
				if (meleeWeaponEquipped == true && calculateDistance(Position, (*it)->Position) < 25)
				{
					(*it)->modifyHealth("decrease", 5);
				}
			}

			for (it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
			{
				if (meleeWeaponEquipped == true && calculateDistance(Position, (*it)->Position) < 25)
				{
					(*it)->modifyHealth("decrease", 5);
				}
			}
		}
	}

	if (rangedWeaponEquipped == true)
	{
		if (Application::IsKeyPressed(VK_LBUTTON))
		{
			playerBullet* bullet = new playerBullet(this->Position, this->Forward, this->Up, this->Right);
			bullets.push_back(bullet);
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);
		for (auto &j : meleeEnemies)
		{
			if (i < bullets.size())
			{
				if (calculateDistance(bullets[i]->getPos(), j->Position) < 8)
				{
					playerBullet* temp = bullets[i];
					j->modifyHealth("decrease", 10);
					std::cout << "enemy took damage" << std::endl;
					bullets.erase(bullets.begin() + i);
					delete temp;
					i = 0;
				}
			}
			else
			{
				i = 0;
			}
		}

		for (auto &k : rangedEnemies)
		{
			if (i < bullets.size())
			{
				if (calculateDistance(bullets[i]->getPos(), k->Position) < 5.f)
				{
					playerBullet* temp = bullets[i];
					k->modifyHealth("decrease", 15);
					std::cout << "enemy took damage" << std::endl;
					bullets.erase(bullets.begin() + i);
					delete temp;
					i = 0;
				}
			}
			else
			{
				i = 0;
			}
		}

		if (i < bullets.size() && bullets[i]->outOfRange)
		{
			playerBullet* temp = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete temp;
			i = 0;
		}
	}

	/*for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);
		for (auto &k : rangedEnemies)
		{
			if (i < bullets.size())
			{
				if (calculateDistance(bullets[i]->getPos(), k->Position) < 5.f)
				{
					playerBullet* temp = bullets[i];
					k->modifyHealth("decrease", 15);
					std::cout << "enemy took damage" << std::endl;
					bullets.erase(bullets.begin() + i);
					delete temp;
					i = 0;
				}
			}
			else
			{
				i = 0;
			}
		}

		if (i < bullets.size() && bullets[i]->outOfRange)
		{
			playerBullet* temp = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete temp;
			i = 0;
		}
	}*/

}

float LandPlayer::calculateDistance(Vector3 playerPos, Vector3 enemyPos)
{
	float dist;

	float x1 = playerPos.x;
	float x2 = enemyPos.x;

	float y1 = playerPos.z;
	float y2 = enemyPos.z;

	float x = x1 - x2;
	float y = y1 - y2;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

LandFPSCamera* LandPlayer::getCam()
{
	return FPS_CAM;
}