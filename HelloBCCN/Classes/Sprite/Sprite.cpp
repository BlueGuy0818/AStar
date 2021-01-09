#include "Sprite.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"
#include "AI\SteeringBehavious.h"
#include "AI\PathFind.h"

Sprite::Sprite()
{
	armature = NULL;

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	speed = WALK_SPEED;
	speedX = 0;
	speedY = 0;
	distX = 0;
	distY = 0;

	originalPosition = ccp(0, 0);
	position = ccp(0, 0);
	targetPosition = ccp(0, 0);

	isTouchMove = false;
	action = STAND;

	direction = DIRECTION_NONE;
	directionX = RIGHT;
	directionY = DIRECTION_NONE;

	nextDirectionX = RIGHT;
	nextDirectionY = DIRECTION_NONE;

	touchNextDirectionX = RIGHT;
	touchNextDirectionY = DIRECTION_NONE;

	isWalk = false;
	hurtCount = 0;

	isAi = false;
	aiType = AI_INIT;
	aiDuration = 0;
	isAstar = false;

	wanderPoint = ccp(0, 0);
	seekPoint = ccp(0, 0);
	fleePoint = ccp(0, 0);
}

Sprite::~Sprite()
{
}

void Sprite::updateEXT(float delta)
{
	stateMachine->executeState();

	if (type == PLAYER)
	{
		list<CCPoint>& astarPathList = PathFind::getTheOnlyInstance()->astarPathList;
		int size = astarPathList.size();

		if (astarPathList.size() != 0)
		{
			if (isAstar == false)
			{
				list<CCPoint>::iterator it = astarPathList.begin();
				CCTMXLayer* mapLayer = mainCity->tiledMap->layerNamed("mainCityLayer");
				targetPosition.x = (*it).x * mainCity->tiledMap->getTileSize().width + mainCity->tiledMap->getTileSize().width / 2;
				targetPosition.y = mainCity->tiledMap->getContentSize().height - (*it).y * mainCity->tiledMap->getTileSize().height - mainCity->tiledMap->getTileSize().height / 2;
				isAstar = true;
				stateMachine->changeState(WALK);
				astarPathList.pop_front();
			}
		}
	}

	if (type == MONSTER)
	{
		if (fightingMap != NULL)
		{
			armature->setPosition(ccp(position.x+fightingMap->position.x, position.y+fightingMap->position.y));
		}
	}
}

void Sprite::setMainCity(MainCity* mainCity)
{
	this->mainCity = mainCity;
}

void Sprite::setFightingMap(FightingMap* fightingMap)
{
	this->fightingMap = fightingMap;
}

void Sprite::setType(int type)
{
	this->type = type;
}

void Sprite::setOriginalPosition(CCPoint& originalPosition)
{
	this->originalPosition = originalPosition;
}

void Sprite::setPosition(CCPoint& position)
{
	this->position = position;
}

void Sprite::setTargetPosition(CCPoint& targetPosition)
{
	this->targetPosition = targetPosition;
}

void Sprite::setTouchMove(bool isTouchMove)
{
	this->isTouchMove = isTouchMove;
}

void Sprite::setDirection(int direction)
{
	this->direction = direction;
}

void Sprite::setDirectionEXT(int directionX, int directionY)
{
	this->directionX = directionX;
	this->directionY = directionY;
}

void Sprite::setNextDirectionX(int nextDirectionX)
{
	this->nextDirectionX = nextDirectionX;
}

void Sprite::setNextDirectionY(int nextDirectionY)
{
	this->nextDirectionY = nextDirectionY;
}

void Sprite::setAction(int action)
{
	this->action = action;

	if (type == MONSTER)
	{
		switch(action)
		{
		case STAND:
			if ((directionX == RIGHT) && (directionY == DIRECTION_NONE))
			{
				armature->getAnimation()->play("Stand");
			}

			if ((directionX == DIRECTION_NONE) && (directionY == DOWN))
			{
				armature->getAnimation()->play("StandDown");
			}
			
			break;
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			armature->getAnimation()->play("Attack");
			break;
		case HURT:
			armature->getAnimation()->play("Hurt");
			break;
		case DEAD:
			armature->getAnimation()->play("Dead");
			break;
		}
	}

	if (type == PLAYER)
	{
		switch(action)
		{
		case STAND:
			if (directionY == UP)
			{
				armature->getAnimation()->play("StandUp");
			}

			if (directionY == DOWN)
			{
				armature->getAnimation()->play("StandDown");
			}

			if (directionX == LEFT)
			{
				armature->getAnimation()->play("StandLeft");
			}

			if (directionX == RIGHT)
			{
				armature->getAnimation()->play("StandRight");
			}

			if ((directionX == RIGHT) && (directionY == DOWN))
			{
				armature->getAnimation()->play("StandRightDown");
			}

			if ((directionX == RIGHT) && (directionY == UP))
			{
				armature->getAnimation()->play("StandRightUp");
			}

			if ((directionX == LEFT) && (directionY == DOWN))
			{
				armature->getAnimation()->play("StandLeftDown");
			}

			if ((directionX == LEFT) && (directionY == UP))
			{
				armature->getAnimation()->play("StandLeftUp");
			}
			break;
		case WALK:

			if (directionY == UP)
			{
				armature->getAnimation()->play("WalkUp");
			}

			if (directionY == DOWN)
			{
				armature->getAnimation()->play("WalkDown");
			}

			if (directionX == LEFT)
			{
				armature->getAnimation()->play("WalkLeft");
			}

			if (directionX == RIGHT)
			{
				armature->getAnimation()->play("WalkRight");
			}

			if ((directionX == RIGHT) && (directionY == DOWN))
			{
				armature->getAnimation()->play("WalkRightDown");
			}

			if ((directionX == RIGHT) && (directionY == UP))
			{
				armature->getAnimation()->play("WalkRightUp");
			}

			if ((directionX == LEFT) && (directionY == DOWN))
			{
				armature->getAnimation()->play("WalkLeftDown");
			}

			if ((directionX == LEFT) && (directionY == UP))
			{
				armature->getAnimation()->play("WalkLeftUp");
			}

			break;
		case ATTACK0:
		case ATTACK1:
		case ATTACK2:
		case ATTACK3:
		case ATTACK4:
			break;
		case HURT:
			break;
		case DEAD:
			break;
		}
	}
}

void Sprite::setIsAi(bool isAi)
{
	this->isAi = isAi;
}

void Sprite::setAI(int aiType, int aiDuration)
{
	this->aiType = aiType;
	this->aiDuration = aiDuration;
}

void Sprite::setStateMachine(StateMachine* stateMachine)
{
	this->stateMachine = stateMachine;
	stateMachine->changeState(STAND);
}