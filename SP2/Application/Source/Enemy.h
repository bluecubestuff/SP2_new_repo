#ifndef ENEMY_H
#define ENEMY_H

#include "AABB.h"
#include "Node.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Application.h"
#include <vector>

using std::vector;

class LandEnemy : public GameObject
{
public:
	LandEnemy(Vector3 pos, int hp);
	~LandEnemy();

	bool enemyIsDead;
	int enemyHP;
	int d;
	Vector3 enemyPos;
	AABB enemyAABB;

	void randomMovement();
	vector<Vector3> Pathfinding(Vector3 enemyPos, Vector3 endGoal);
	void PathfindingMovement(vector<Vector3> AIpath);
};

#endif

