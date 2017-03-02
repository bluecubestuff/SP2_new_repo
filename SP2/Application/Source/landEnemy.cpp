#include "landEnemy.h"
#include "landPlayer.h"
#include <list>

using std::list;

LandEnemy::LandEnemy(Vector3 pos, Vector3 endGoal, float hp, float speed)
{
	Position = pos;
	enemyGoal = endGoal;
	Forward = Vector3(0, 0, 1);
	Up = Vector3(0, 1, 0);
	Right = Vector3(1, 0, 0);
	Health = hp;
	moveSpeed = speed;
	enemyIsDead = false;
	Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
}

LandEnemy::~LandEnemy()
{

}

void LandEnemy::enemyInit(char landGrid[2500][2500], Vector3 startPos, Vector3 endGoal)
{
	//calculate paths to reach the goal and return to its starting position
	savedAIpath = Pathfinding(landGrid, startPos, endGoal);
	savedAIreturnPath = Pathfinding(landGrid, endGoal, startPos);

	AIpath = savedAIpath;
	AIreturnPath = savedAIreturnPath;
}

void LandEnemy::meleeUpdate(double dt, LandPlayer* playerObj)
{
	if (enemyIsDead == false)
	{
		meleePathfindingMovement(dt, playerObj->Position, playerObj->getter("forward"));
		meleeCombat(dt, playerObj);
		Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
	}
}

void LandEnemy::rangedUpdate(double dt, LandPlayer* playerObj)
{
	if (enemyIsDead == false)
	{
		rangedPathfindingMovement(dt, playerObj);
		Stamp = Mtx44(Right.x, Right.y, Right.z, 0, Up.x, Up.y, Up.z, 0, Forward.x, Forward.y, Forward.z, 0, Position.x, Position.y, Position.z, 1);
	}
}

void LandEnemy::meleeCombat(double dt, LandPlayer* playerObj)
{
	if (abs(calculateDistance(playerObj->Position, Position) < 20))
	{
		playerObj->modifyHealth("decrease", 3);
		std::cout << playerObj->getHealth() << std::endl;
	}
}

void LandEnemy::AIPursuit(double dt, Vector3 playerPos, Vector3 playerForward)
{
	float rotateSpeed = 50 * dt;

	target = playerPos - this->Position;

	try
	{
		/*std::cout << "function called" << std::endl;*/

		if (this->Forward != target.Normalized())
		{
					Vector3 temp = this->Forward.Cross(target.Normalized());
					temp.Normalize();
					Mtx44 rotate;
					rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);

					this->Forward = rotate * this->Forward;
					this->Right = rotate * this->Right;
		}

				this->Position.x += this->Forward.x * dt * moveSpeed;
				this->Position.z += this->Forward.z * dt * moveSpeed;
	}
		
	catch (std::exception& e)
	{
		std::cout << "nothing" << std::endl;
	}
}

void LandEnemy::AIShoot(double dt, LandPlayer* playerObj)
{
	float rotateSpeed = 150 * dt;

	target = playerObj->Position - this->Position;

		try
		{
			/*std::cout << "function called" << std::endl;*/

			if (this->Forward != target.Normalized())
			{
				Vector3 temp = this->Forward.Cross(target.Normalized());
				temp.Normalize();
				Mtx44 rotate;
				rotate.SetToRotation(rotateSpeed, temp.x, temp.y, temp.z);

				this->Forward = rotate * this->Forward;
				this->Right = rotate * this->Right;
			}

			enemyBullet* bullet = new enemyBullet(this->Position, this->Forward, this->Up, this->Right);
			enemyBullets.push_back(bullet);

		}

		catch (std::exception& e)
		{
			std::cout << "nothing" << std::endl;
		}

	for (int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i]->Update(dt);

		if (i < enemyBullets.size())
		{
			if (abs(calculateDistance(enemyBullets[i]->getPos(), playerObj->Position) < 5.f))
			{
					enemyBullet* temp = enemyBullets[i];
					playerObj->modifyHealth("decrease", 1);
					std::cout << "enemy took damage" << std::endl;
					enemyBullets.erase(enemyBullets.begin() + i);
					delete temp;
					i = 0;
			}
		}
		else
		{
			i = 0;
		}

		if (i < enemyBullets.size() && enemyBullets[i]->outOfRange)
		{
			enemyBullet* temp = enemyBullets[i];
			enemyBullets.erase(enemyBullets.begin() + i);
			delete temp;
			i = 0;
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

vector<Vector3*> LandEnemy::Pathfinding(char landGrid[2500][2500], Vector3 startPos, Vector3 endGoal)
{
	vector<Vector3*> path; //create path vector to store the nodes the AI traverses

	//set positions of start and end nodes

	start->pos.x = startPos.x;
	start->pos.z = startPos.z;

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


				if (successor->open) //check if the successor node is on the open list
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

	std::cout << "loop broken" << std::endl;
	std::cout << n << std::endl;

	//reset open and closed lists
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
		n++;
	}

	return path;
}

void LandEnemy::setPosition(Vector3* position)
{
	Position.x = position->x;
	Position.z = position->z;
}

void LandEnemy::meleePathfindingMovement(double dt, Vector3 playerPos, Vector3 playerForward)
{	
	if (AIpath.size() != 0)
	{
		if (abs(calculateDistance(playerPos, Position) <= 70))
		{
			AIPursuit(dt, playerPos, playerForward);
		}
		else if (abs(calculateDistance(playerPos, Position) > 70))
		{
			setPosition(AIpath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
			AIpath.pop_back(); //pops the last element, repeat
			/*std::cout << "AI moved" << std::endl;*/
		}
	}
	else if (AIreturnPath.size() != 0 && AIpath.size() == 0)
	{
		if (abs(calculateDistance(playerPos, Position) <= 70))
		{
			AIPursuit(dt, playerPos, playerForward);
		}
		else if (abs(calculateDistance(playerPos, Position) > 70))
		{
			setPosition(AIreturnPath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
			AIreturnPath.pop_back(); //pops the last element, repeat
			/*std::cout << "AI moved" << std::endl;*/
		}
	}

	if (AIpath.size() == 0 && AIreturnPath.size() == 0)
	{
		AIpath = savedAIpath;
		AIreturnPath = savedAIreturnPath;
	}
}

void LandEnemy::rangedPathfindingMovement(double dt, LandPlayer* playerObj)
{
	if (AIpath.size() != 0)
	{
		if (abs(calculateDistance(playerObj->Position, Position)) <= 100)
		{
			AIShoot(dt, playerObj);
		}
		else if (abs(calculateDistance(playerObj->Position, Position)) > 100)
		{
			enemyBullets.clear();
			setPosition(AIpath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
			AIpath.pop_back(); //pops the last element, repeat
			/*std::cout << "AI moved" << std::endl;*/
		}
		
	}
	if (AIreturnPath.size() != 0 && AIpath.size() == 0)
	{
		if (abs(calculateDistance(playerObj->Position, Position)) <= 100)
		{
			AIShoot(dt, playerObj);
		}
		else if (abs(calculateDistance(playerObj->Position, Position)) > 100)
		{
			setPosition(AIreturnPath.back()); //setPosition is called to change position of enemy to the element currently at the back of the vector
			AIreturnPath.pop_back(); //pops the last element, repeat
			/*std::cout << "AI moved" << std::endl;*/
		}
		
		
	}
	if (AIpath.size() == 0 && AIreturnPath.size() == 0)
	{
		AIpath = savedAIpath;
		AIreturnPath = savedAIreturnPath;
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

