#ifndef ENEMY_H
#define ENEMY_H

#include "AABB.h"
#include "Node.h"
#include "Vector3.h"
#include "Item.h"
#include "landEntity.h"
#include "Application.h"
#include <iostream>
#include <vector>

using std::vector;

class LandEnemy : public LandEntity
{
public:
	LandEnemy(Vector3 pos, float hp, float shields);
	~LandEnemy();

	bool enemyIsDead;
	int d;
	/*Vector3 enemyPos;*/
	void enemyUpdate();
	void randomMovement();
	vector<Vector3*> Pathfinding(char landGrid[2500][2500], Vector3 endGoal);
	void PathfindingMovement();
	void setPosition(Vector3* position);
	vector<Vector3*> AIpath;
	vector<Vector3*> AIreturnPath;
	vector<Item> enemyLootTable;

	//Pathfinding nodes

	Node *start = new Node;
	Node *end = new Node;
	Node *current = new Node;
	Node *successor = new Node;

};

#endif

