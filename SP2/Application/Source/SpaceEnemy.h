#ifndef _SPACE_ENEMY_H
#define _SPACE_ENEMY_H

//class for enemy behaviour
class SpaceEnemy
{
public:
	enum Passive_t
	{
		PIdle,
		PChase,
		PAttack,
		PDeath,
		PRetreat,
		PBreak_Off
	};

	enum Aggressive_t
	{
		AIdle,
		AChase,
		AAttack,
		ADeath,
		ARetreat,
		ABreak_Off
	};
private:
};

#endif