#ifndef __STEERING_BEHAVIOUS__
#define __STEERING_BEHAVIOUS__

#include "Sprite\Sprite.h"
#include "States.h"

enum
{
	AI_INIT = 0,
	AI_STAND,
	AI_WANDER,
	AI_SEEK,
	AI_FLEE,
	AI_PURSUIT,
	AI_ATTACK
};

enum
{
	AI_ATTACK0,
	AI_ATTACK1,
	AI_ATTACK2,
	AI_ATTACK3,
	AI_ATTACK4,
};

class SteeringBehavious
{
public:

	SteeringBehavious();
	~SteeringBehavious();

	int probability;

	void updateEXT(Sprite* sprite);

	int getProbability(int* probabilitys, int type);
};

#endif