#include "Input.h"
#include "AI\StateMachine.h"
#include "..\HelloBCCN.h"

void Input::update()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    

	Player* player = HelloBCCN::getTheOnlyInstance()->mainCityScene->player;

	bool isWalk = false;

	player->setNextDirectionX(DIRECTION_NONE);
	player->setNextDirectionY(DIRECTION_NONE);

	if (KEY_DOWN(VK_LEFT) || KEY_DOWN('S')) 
	{
		player->setNextDirectionX(LEFT);
		isWalk = true;
	}

	if (KEY_DOWN(VK_RIGHT) || KEY_DOWN('F')) 
	{
		player->setNextDirectionX(RIGHT);
		isWalk = true;
	}

	if (KEY_DOWN(VK_UP) || KEY_DOWN('E')) 
	{
		player->setNextDirectionY(UP);
		isWalk = true;
	}

	if (KEY_DOWN(VK_DOWN) || KEY_DOWN('D')) 
	{
		player->setNextDirectionY(DOWN);
		isWalk = true;
	}

	if (KEY_DOWN('J')) 
	{
		player->stateMachine->changeState(ATTACK0);
	}

	if (KEY_DOWN('U')) 
	{
		player->stateMachine->changeState(ATTACK0);
	}

	if (KEY_DOWN('H')) 
	{
		player->stateMachine->changeState(ATTACK0);
	}

	if (KEY_DOWN('K')) 
	{
		player->stateMachine->changeState(ATTACK0);
	}

	if (player->isTouchMove == false)
	{
		if (isWalk == false)
		{
			if ((player->stateMachine->getCurrentState() != ATTACK0) &&
				(player->stateMachine->getCurrentState() != ATTACK1) &&
				(player->stateMachine->getCurrentState() != ATTACK2) &&
				(player->stateMachine->getCurrentState() != ATTACK3) &&
				(player->stateMachine->getCurrentState() != ATTACK4)
				)
			{
				player->setNextDirectionX(player->directionX);
				player->setNextDirectionY(player->directionY);
				player->stateMachine->changeState(STAND);
			}
		}
		else
		{
			if ((player->stateMachine->getCurrentState() != ATTACK0) &&
				(player->stateMachine->getCurrentState() != ATTACK1) &&
				(player->stateMachine->getCurrentState() != ATTACK2) &&
				(player->stateMachine->getCurrentState() != ATTACK3) &&
				(player->stateMachine->getCurrentState() != ATTACK4)
				)
			{
				player->setTouchMove(false);
				player->stateMachine->changeState(WALK);
			}
		}
	}

#endif
}