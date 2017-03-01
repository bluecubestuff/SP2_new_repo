#ifndef LAND_ENEMY_H
#define LAND_ENEMY_H

#include "AABB.h"
#include "Node.h"
#include "Vector3.h"
#include "Item.h"
#include "landEntity.h"
#include "Application.h"
#include "enemyBullet.h"
#include "Mtx44.h"
#include <iostream>
#include <vector>

using std::vector;

class LandPlayer;

class LandEnemy : public LandEntity
{
public:
	LandEnemy(Vector3 pos, float hp, float speed);
	~LandEnemy();

	bool enemyIsDead;
	int d;
	float moveSpeed;
	void meleeUpdate(double dt, LandPlayer* playerObj);
	void rangedUpdate(double dt, LandPlayer* playerObj);
	void meleeCombat(double dt, LandPlayer* playerObj);
	void randomMovement();
	void enemyInit(char landGrid[2500][2500], Vector3 startPos, Vector3 endGoal);
	vector<Vector3*> Pathfinding(char landGrid[2500][2500], Vector3 startPos, Vector3 endGoal);
	void meleePathfindingMovement(double dt, Vector3 playerPos, Vector3 playerForward);
	void rangedPathfindingMovement(double dt, LandPlayer* playerObj);
	void setPosition(Vector3* position);
	void AIPursuit(double dt, Vector3 playerPos, Vector3 playerForward);
	void AIShoot(double dt, LandPlayer* playerObj);
	float calculateDistance(Vector3 playerPos, Vector3 enemyPos);
	vector<Vector3*> savedAIpath;
	vector<Vector3*> savedAIreturnPath;
	vector<Vector3*> AIpath;
	vector<Vector3*> AIreturnPath;
	vector<enemyBullet*> enemyBullets;
	vector<Item*> enemyLootTable;
	Vector3 target;
	Mtx44 Stamp;

	//Pathfinding nodes

	Node *start = new Node;
	Node *end = new Node;
	Node *current = new Node;
	Node *successor = new Node;

};

#endif

