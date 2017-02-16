#include "Node.h"

Node::Node()
{
	parent = NULL;
	closed = false;
	open = false;

	pos.x = pos.z = f = g = h = 0;
}

Node::Node(int x, int z, bool w)
{
	Node();
	this->walkable = w;
	this->pos.x = x;
	this->pos.z = z;
}

Node::~Node()
{

}
Node* Node::getNode(float successorPosX, float successorPosY)
{
	Node* temp = new Node;
	temp->pos.x = successorPosX;
	temp->pos.y = successorPosY;

	return temp;
}

Vector3 Node::getNodePosition(Node* n)
{
	Vector3 newPos = n->pos;

	return newPos;
}

Node* Node::getParent()
{
	return parent;
}

void Node::setParent(Node *n)
{
	parent = n;
}

float Node::getX()
{
	return pos.x;
}

float Node::getZ()
{
	return pos.z;
}

int Node::calculateGscore(Node* n)
{
	return n->g++;
}

int Node::calculateHscore(Node* n)
{
	return (abs(n->pos.x - pos.x) + abs(n->pos.z - pos.z));
}

int Node::getFscore()
{
	return f;
}

int Node::getGscore()
{
	return g;
}

int Node::getHscore()
{
	return h;
}

void Node::computeFscore(Node *end)
{
	g = calculateGscore(parent);
	h = calculateHscore(parent);
	f = g + h;
}

bool Node::hasParent()
{
	return parent != NULL;
}