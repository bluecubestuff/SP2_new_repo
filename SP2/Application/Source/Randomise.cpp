#include "Randomise.h"
#include "Weapon.h"
#include <cstdlib>

Randomise::Randomise(){}

Randomise::~Randomise(){}

unsigned Randomise::generate_range(unsigned from, unsigned to)
{
	return(rand() % (to - from)) + from;
}



