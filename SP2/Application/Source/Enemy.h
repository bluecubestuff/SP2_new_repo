#ifndef ENEMY_H
#define ENEMY_H

#include "AABB.h"
#include "Node.h"
#include "Vector3.h"
#include "Item.h"
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
	void enemyUpdate();
	void randomMovement();
	vector<Vector3*> Pathfinding(char landGrid[2500][2500], Vector3 endGoal);
	void PathfindingMovement();
	void setPosition(Vector3* position);
	vector<Vector3*> AIpath;
	vector<Item> enemyLootTable;

};

#endif

