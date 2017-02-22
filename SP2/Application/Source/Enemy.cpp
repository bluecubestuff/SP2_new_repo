#include "Enemy.h"
#include <list>

using std::list;

LandEnemy::LandEnemy(Vector3 pos, int hp)
{
	enemyPos = pos;
	enemyHP = hp;
	enemyIsDead = false;
}

LandEnemy::~LandEnemy()
{

}

void LandEnemy::enemyUpdate()
{
	if (enemyIsDead == false)
	{

	}
}

vector<Vector3*> LandEnemy::Pathfinding(double_land_array landGrid, Vector3 endGoal)
{
	vector<Vector3*> path; //create the vector of Vector3 pointers that stores the nodes the enemy travels through

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
			for (int z = -1; z < 2; z++)
			{
				if (x == 0 && z == 0) //checks if successor node is the current node;
				{
					continue;
				}
				else
				{
					successor = current->getNode(current->getX() + x, current->getZ());
					successor->getPointInGrid(landGrid);
				} //set the pos of the successor node

				if (successor->closed == true)
				{
					continue;
				}

				//check for collision according to character of non-walkable square in grid
				//if (landGrid[successor->pos.x][successor->pos.y] == '') 
				//{
				//	continue;
				//}

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
		}
	
		n++;

	}

	for (i = openList.begin(); i != openList.end(); ++i)
	{
		(*i)->open = false;
	}
	for (i = closedList.begin(); i != closedList.end(); ++i)
	{
		(*i)->closed = false;
	}

	//push path nodes into path vector
	while (current->hasParent() && current != start)
	{
		path.push_back(current->getNodePosition()); //pushes the path nodes into the path vector
		current = current->getParent(); //current node will change to the parent of the current node;
		n++;
	}

	AIpath = path;

	return path;
}

void LandEnemy::setPosition(Vector3* position)
{
	enemyPos.x = position->x;
	enemyPos.y = position->y;
}

void LandEnemy::PathfindingMovement() 
{	
	vector<Vector3*>::reverse_iterator it; //iterator
	
	for (it = AIpath.rend(); it != AIpath.rbegin(); it++) //iterates through the vector using a for loop
	{
		setPosition(AIpath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
		AIpath.pop_back(); //pops the last element, repeat
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

