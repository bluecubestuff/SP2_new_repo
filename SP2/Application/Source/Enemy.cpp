#include "Enemy.h"

Enemy::Enemy(StudioProject* scene, Vector3 pos, float size, int hp)
{
	enemyPos = pos;
	enemyHP = hp;
	enemyAABB.pt_Max.x = pos.x + 5;
	enemyAABB.pt_Max.y = pos.y + 5;
	enemyAABB.pt_Max.z = pos.z + 5;
	enemyAABB.pt_Min.x = pos.x - 5;
	enemyAABB.pt_Min.y = pos.y - 5;
	enemyAABB.pt_Min.z = pos.z - 5;
}

Enemy::~Enemy()
{

}