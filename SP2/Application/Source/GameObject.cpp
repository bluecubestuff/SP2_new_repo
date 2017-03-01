#include "StudioProject.h"
#include "GameObject.h"

int GameObject::count_ = 0;

GameObject::~GameObject()
{
	count_--;
}
int GameObject::getCount()
{
	return count_;
}
GameObject::GameObject()
{
	count_++;
}