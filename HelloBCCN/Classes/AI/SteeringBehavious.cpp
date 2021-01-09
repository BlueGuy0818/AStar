#include "SteeringBehavious.H"
#include "..\HelloBCCN.h"

SteeringBehavious::SteeringBehavious()
{}

SteeringBehavious::~SteeringBehavious()
{
}

void SteeringBehavious::updateEXT(Sprite* sprite)
{
	if ((sprite->stateMachine->getCurrentState() != STAND) &&
		(sprite->stateMachine->getCurrentState() != WALK)
		)
	{
		return;
	}

	int aiProbabilitys[6] = {20, 20, 20, 20, 10, 10};
	int aiAttackProbabilitys[5] = {20, 20, 20, 20, 20};

	Player* player = HelloBCCN::getTheOnlyInstance()->mainCityScene->player;

	switch(sprite->aiType)
	{
	case AI_INIT:

		probability = rand() % 100;

		if (probability < getProbability(aiProbabilitys, AI_STAND))
		{
			// ¾²Ö¹
			sprite->aiType = AI_STAND;
		}
		else if (probability < getProbability(aiProbabilitys, AI_WANDER))
		{
			// ÅÇ»²
			sprite->aiType = AI_WANDER;
			sprite->wanderPoint = sprite->position;
		}
		else if (probability < getProbability(aiProbabilitys, AI_SEEK))
		{
			// ¿¿½ü
			sprite->aiType = AI_SEEK;
			sprite->seekPoint = player->position;
		}
		else if (probability < getProbability(aiProbabilitys, AI_FLEE))
		{
			// Ô¶Àë
			sprite->aiType = AI_FLEE;

			int x = CCRANDOM_MINUS1_1() * 200;
			int y = CCRANDOM_MINUS1_1() * 200;

			x = ((x < 0) ? (x-200) : (x+200));
			y = ((y < 0) ? (y-200) : (y+200));

			sprite->fleePoint.x = player->position.x + x;
			sprite->fleePoint.y = player->position.y + y;
		}
		else if (probability < getProbability(aiProbabilitys, AI_PURSUIT))
		{
			// ×·Öð
			sprite->aiType = AI_PURSUIT;
		}
		else if (probability < getProbability(aiProbabilitys, AI_ATTACK))
		{
			// ¹¥»÷
			sprite->aiType = AI_ATTACK;
		}

		break;
	case AI_STAND:
		sprite->aiDuration++;
	
		if (sprite->aiDuration < 60)
		{
			sprite->stateMachine->changeState(STAND);
		}
		else
		{
			sprite->aiType = AI_INIT;
			sprite->aiDuration = 0;
		}

		break;
	case AI_WANDER:

		sprite->aiDuration++;

		if (sprite->aiDuration < 60)
		{
			if (sprite->aiDuration % 20 == 0)
			{
				int x = CCRANDOM_MINUS1_1() * 300;
				sprite->setTargetPosition(ccp(sprite->wanderPoint.x+x, sprite->wanderPoint.y));
				sprite->stateMachine->changeState(WALK);
			}
		}
		else
		{
			sprite->stateMachine->changeState(STAND);
			sprite->aiType = AI_INIT;
			sprite->aiDuration = 0;
		}

		break;
	case AI_SEEK:

		sprite->aiDuration++;

		if (sprite->aiDuration < 60)
		{
			sprite->setTargetPosition(sprite->seekPoint);
			sprite->stateMachine->changeState(WALK);
		}
		else
		{
			sprite->stateMachine->changeState(STAND);
			sprite->aiType = AI_INIT;
			sprite->aiDuration = 0;
		}

		break;
	case AI_FLEE:

		sprite->aiDuration++;

		if (sprite->aiDuration < 60)
		{
			sprite->setTargetPosition(sprite->fleePoint);
			sprite->stateMachine->changeState(WALK);
		}
		else
		{
			sprite->stateMachine->changeState(STAND);
			sprite->aiType = AI_INIT;
			sprite->aiDuration = 0;
		}

		break;
	case AI_PURSUIT:

		sprite->aiDuration++;

		if (sprite->aiDuration < 60)
		{
			CCPoint dist = ccp(sprite->position.x-player->position.x, sprite->position.y-player->position.y);

			float distX = dist.x;
			float distY = dist.y;

			if ((distX == 0) && (distY == 0))
			{
				break;
			}

			float d = sqrt(distX * distX + distY * distY);

			if (d > 200)
			{
				sprite->setTargetPosition(ccp(player->position.x, player->position.y));
				sprite->stateMachine->changeState(WALK);
			}
		}
		else
		{
			sprite->stateMachine->changeState(STAND);
			sprite->aiType = AI_INIT;
			sprite->aiDuration = 0;
		}

		break;
	case AI_ATTACK:

		if (sprite->action == ATTACK0 ||
			sprite->action == ATTACK1 ||
			sprite->action == ATTACK2 ||
			sprite->action == ATTACK3 ||
			sprite->action == ATTACK4 
			)
		{
			break;
		}

		probability = rand() % 100;

		if (probability < getProbability(aiAttackProbabilitys, AI_ATTACK0))
		{
			// ¹¥»÷1
			sprite->stateMachine->changeState(ATTACK0);
		}
		else if (probability < getProbability(aiAttackProbabilitys, AI_ATTACK1))
		{
			// ¹¥»÷2
			sprite->stateMachine->changeState(ATTACK1);
		}
		else if (probability < getProbability(aiAttackProbabilitys, AI_ATTACK2))
		{
			// ¹¥»÷3
			sprite->stateMachine->changeState(ATTACK2);
		}
		else if (probability < getProbability(aiAttackProbabilitys, AI_ATTACK3))
		{
			// ¹¥»÷4
			sprite->stateMachine->changeState(ATTACK3);
		}
		else if (probability < getProbability(aiAttackProbabilitys, AI_ATTACK4))
		{
			// ¹¥»÷5
			sprite->stateMachine->changeState(ATTACK4);
		}

		break;
	}
}

int SteeringBehavious::getProbability(int* probabilitys, int type)
{
	int sumProbability = 0;

	for (int i = 0; i < type; i++)
	{
		sumProbability += probabilitys[i];
	}

	return sumProbability;
}