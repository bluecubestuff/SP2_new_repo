#ifndef AI_H
#define AI_H

#include "Enemy.h"
#include "Node.h"
#include <vector>

using std::vector;

class EnemyAI : public Enemy
{
	int d;
	void randomMovement(Vector3 enemyPos);
	vector<Vector3> Pathfinding(Vector3 enemyPos, Vector3 endGoal);
	void PathfindingMovement(vector<Vector3> AIpath);
};

#endif