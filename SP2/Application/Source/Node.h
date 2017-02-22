#ifndef NODE_H
#define NODE_H

#include "Vector3.h"
#include "LandGenerate.h"

struct Node
{
public:
	bool open;
	bool closed;
	Vector3 pos;
	float f;
	float g;
	float h;
	double_land_array nodeGridPosition;
	Node* parent;

	Node();
	Node(float x, float z);
	~Node();
	Node* getNode(float successorPosX, float successorPosY);
	Node* getParent();
	Vector3* getNodePosition();
	void getPointInGrid(double_land_array landGrid);
	void setParent(Node *n);
	float getX();
	float getZ();
	int getFscore();
	int getGscore();
	int getHscore();
	int calculateGscore(Node *n);
	int calculateHscore(Node* n);
	void computeFscore(Node *end);

	bool hasParent();
};

#endif