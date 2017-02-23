#include "Randomise.h"
#include "Weapon.h"
#include <cstdlib>
#include <time.h>

Randomise::Randomise(){
	
}

Randomise::~Randomise(){}

unsigned Randomise::generate_range(unsigned from, unsigned to)
{
	
	return(rand() % (to - from)) + from;
}



