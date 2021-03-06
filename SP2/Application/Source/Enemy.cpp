#include "Enemy.h"
#include <list>

using std::list;

LandEnemy::LandEnemy(Vector3 pos, int hp)
{
	enemyPos = pos;
	enemyHP = hp;
	enemyAABB.pt_Max.x = pos.x + 5;
	enemyAABB.pt_Max.y = pos.y + 5;
	enemyAABB.pt_Max.z = pos.z + 5;
	enemyAABB.pt_Min.x = pos.x - 5;
	enemyAABB.pt_Min.y = pos.y - 5;
	enemyAABB.pt_Min.z = pos.z - 5;
	enemyIsDead = false;
}

LandEnemy::~LandEnemy()
{

}

vector<Vector3> LandEnemy::Pathfinding(Vector3 enemyPos, Vector3 endGoal)
{
	vector<Vector3> AIpath; //create the vector of Vector3 that stores the nodes the enemy travels through

	//define nodes for use
	Node *start = new Node;
	start->pos.x = enemyPos.x;
	start->pos.z = enemyPos.z;

	Node *end = new Node;
	end->pos.x = endGoal.x;
	end->pos.z = endGoal.z;

	Node *current = new Node;
	Node *successor = new Node;

	//create open and closed lists
	list<Node*> openList;
	list<Node*> closedList;
	list<Node*>::iterator i;

	unsigned int n = 0;

	//push back the starting node into the open list
	openList.push_back(start);
	start->open = true;

	while (n == 0 || (current != end && n < 100))
	{
		for (i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getFscore() <= current->getFscore()) //search for node with the lowest F score in the open list
			{
				current = (*i);
			}
		}

		if (current == end) //breaks out of the loop if enemy reaches the end node
		{
			break;
		}

		openList.remove(current); //pop current node with lowest f score from the open list
		current->open = false;

		closedList.push_back(current); //push current node into the closed list
		current->closed = true;

		for (int x = -1; x < 2; x++) //searches for successor nodes
		{
			if (x == 0) //checks if successor node is the current node;
			{
				continue;
			}

			successor = current->getNode(current->getX() + x, current->getZ()); //set the pos of the successor node

			/*	if ()																	//check for collision
			{
			continue;
			}*/

			if (successor->open == true) //check if the successor node is on the open list
			{
				if (successor->getGscore() > successor->calculateGscore(current)) //checks if the G score of the current node is less than the G score of the successor node in the open and closed lists
				{																  //sets the parent node of the successor node to the current node
					successor->setParent(current);
					successor->computeFscore(end); //calculates the successor's F score
				}
			}
			else
			{
				openList.push_back(successor);
				successor->open = true;

				successor->setParent(current);
				successor->computeFscore(end);

			}
		}
		for (int z = -1; z < 2; z++)
		{
			if (z == 0) //checks if successor node is the current node;
			{
				continue;
			}

			successor = current->getNode(current->getX(), current->getZ() + z); 

			if (successor->open == true) 
			{
				if (successor->getGscore() > successor->calculateGscore(current)) 
				{																  
					successor->setParent(current);
					successor->computeFscore(end); 
				}
			}
			else
			{
				openList.push_back(successor);
				successor->open = true;

				successor->setParent(current);
				successor->computeFscore(end);

			}
		}
		n++;
	}

	//push path nodes into path vector
	return AIpath;
}

void LandEnemy::PathfindingMovement(vector<Vector3> AIpath)
{	
	vector<Vector3>::reverse_iterator it;

	for (it = AIpath.rbegin(); it != AIpath.rend(); ++it)
	{
		enemyPos = (*it);
		cout << (*it) << endl;
	}
}

void LandEnemy::randomMovement() 
{
		d = rand() % 1 + 4;
		if (d == 1)
		{
			enemyPos.x++;
		}
		else if (d == 2)
		{
			enemyPos.x--;
		}
		else if (d == 3)
		{
			enemyPos.z++;
		}
		else if (d == 4)
		{
			enemyPos.z--;
		}
}

