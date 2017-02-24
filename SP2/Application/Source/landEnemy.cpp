#include "landEnemy.h"
#include <list>

using std::list;

LandEnemy::LandEnemy(Vector3 pos, Vector3 f, Vector3 r, float hp, float speed)
{
	Position = pos;
	Forward = f;
	Up = Vector3(0, 1, 0);
	Right = r;
	Health = hp;
	moveSpeed = speed;
	enemyIsDead = false;
}

LandEnemy::~LandEnemy()
{

}

void LandEnemy::Update(double dt, Vector3 playerPos, Vector3 playerForward)
{
	
}

void LandEnemy::AIPursuit(double dt, Vector3 playerPos, Vector3 playerForward)
{
	float rotateSpeed = 50 * dt;

	if (enemyIsDead == false)
	{
		target = playerPos - this->Position;

		try
		{
			std::cout << "function called" << std::endl;

			if (abs(calculateDistance(playerPos, Position) <= 70))
			{
				std::cout << "within range" << std::endl;
				if (this->Forward != target.Normalized())
				{
					Vector3 temp = this->Forward.Cross(target.Normalized());
					temp.Normalize();
					Mtx44 rotate;
					rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);

					this->Forward = rotate * this->Forward;
					this->Up = rotate * this->Up;
					this->Right = rotate * this->Right;
				}
				this->Position.x += this->Forward.x * dt * moveSpeed;
				this->Position.z += this->Forward.z * dt * moveSpeed;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "nothing" << std::endl;
		}
		
	}
}

float LandEnemy::calculateDistance(Vector3 playerPos, Vector3 enemyPos)
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

vector<Vector3*> LandEnemy::Pathfinding(char landGrid[2500][2500], Vector3 endGoal)
{
	vector<Vector3*> path; //create the vector of Vector3 pointers that stores the nodes the enemy travels through

	//set positions of start and end nodes

	start->pos.x = Position.x;
	start->pos.z = Position.z;


	end->pos.x = endGoal.x;
	end->pos.z = endGoal.z;

	//create open and closed lists
	list<Node*> openList;
	list<Node*> closedList;
	list<Node*>::iterator it;

	unsigned int n = 0;

	//push back the starting node into the open list
	openList.push_back(start);
	start->open = true;

	while (n == 0 || (current != end && n < 500)) //limited to moving a maximum of 499 spaces due to performance issues
	{
		for (it = openList.begin(); it != openList.end(); ++it)
		{
			if (it == openList.begin() || (*it)->getFscore() <= current->getFscore()) //search for the node with the lowest F score in the open list
			{
				current = (*it);
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
		
		for (int i = -1; i < 2; i++) //searches for successor nodes
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0) //checks if successor node is the current node;
				{
					continue;
				}

				successor = current->getNode(current->getX() + i, current->getZ() + j);

				int x = successor->pos.x;
				int z = successor->pos.z;

				if (successor->closed == true)
				{
					continue;
				}

				if (landGrid[x][z] == 'F')
				{
					std::cout << "Collision detected" << std::endl;
					continue;
				}

				//check for collision according to character of non-walkable square in grid


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

	for (it = openList.begin(); it != openList.end(); ++it)
	{
		(*it)->open = false;
	}
	for (it = closedList.begin(); it != closedList.end(); ++it)
	{
		(*it)->closed = false;
	}

	//push path nodes into path vector
	while (current->hasParent() && current != start)
	{
		path.push_back(current->getNodePosition()); //pushes the path nodes into the path vector
		//cout << current->getNodePosition() << endl;
		current = current->getParent(); //current node will change to the parent of the current node
	}

	return path;
}

void LandEnemy::setPosition(Vector3* position)
{
	Position.x = position->x;
	Position.z = position->z;
}

void LandEnemy::PathfindingMovement() 
{	
	if (AIpath.size() != 0)
	{
		setPosition(AIpath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
		AIpath.pop_back(); //pops the last element, repeat
		std::cout << "AI moved" << std::endl;
	}
	else if (AIreturnPath.size() != 0)
	{
		setPosition(AIreturnPath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
		AIpath.pop_back(); //pops the last element, repeat
		std::cout << "AI moved" << std::endl;
	}
}

void LandEnemy::randomMovement() 
{
		d = rand() % 1 + 4;

		if (d == 1)
		{
			Position.x++;
		}
		else if (d == 2)
		{
			Position.x--;
		}
		else if (d == 3)
		{
			Position.z++;
		}
		else if (d == 4)
		{
			Position.z--;
		}
}

