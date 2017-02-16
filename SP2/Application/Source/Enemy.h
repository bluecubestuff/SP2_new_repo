#ifndef ENEMY_H
#define ENEMY_H

#include "StudioProject.h"
#include "AABB.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Application.h"

class Enemy : public GameObject
{
public:
	Enemy(StudioProject* scene, Vector3 pos, float size, int hp);
	~Enemy();

	bool enemyIsDead;
	int enemyHP;
	Vector3 enemyPos;
	AABB enemyAABB;
};

#endif