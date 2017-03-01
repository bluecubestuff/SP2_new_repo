#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>

using namespace std;

class GameObject
{
public:
	virtual ~GameObject();
	string getName(void);
	static int getCount();

private:
	static int count_;

protected:
	GameObject();
};

#endif