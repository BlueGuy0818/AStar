#ifndef __SPRITE__
#define __SPRITE__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "TileMap\MainCity.h"
#include "TileMap\FightingMap.h"

#include "AI\StateMachine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace gui;

enum DIRECTION
{
	DIRECTION_NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFT_UP,
	RIGHT_DOWN,
	LEFT_DOWN,
	RIGHT_UP
};

enum SPRITE_TYPE
{
	PLAYER = 0,
	MONSTER = 1,
	PET = 2
};

#define WALK_SPEED 12

class Camera;
class StateMachine;

class Sprite
{
public:
	Sprite();
	~Sprite();

	MainCity* mainCity;
	FightingMap* fightingMap;
	CCArmature* armature;

	CCSize visibleSize;
	float speed;
	float speedX;
	float speedY;
	float distX;
	float distY;

	CCPoint originalPosition;
	CCPoint position;
	CCPoint targetPosition;

	bool isTouchMove;

	int type;
	int action;
	int direction;
	int directionX;
	int directionY;

	int nextDirectionX;
	int nextDirectionY;

	int touchNextDirectionX;
	int touchNextDirectionY;

	int face;
	bool isWalk;
	int hurtCount;

	bool isFriend;
	bool isBack;

	bool isAi;
	int aiType;
	int aiDuration;

	bool isAstar;
	StateMachine* stateMachine;

	CCPoint wanderPoint;
	CCPoint seekPoint;
	CCPoint fleePoint;

	Sprite* attackSprite;

	UILayer* uiBloodLayer;

	CCLabelTTF* positionLabel;
	
	CCLabelTTF* boundingBoxLabel[4];
	
	CCSprite* shadowSprite;

	void updateEXT(float delta);

	void setMainCity(MainCity* mainCity);

	void setFightingMap(FightingMap* fightingMap);

	void setCamera(Camera* camera);

	void setType(int type);

	void setOriginalPosition(CCPoint& originalPosition);

	void setPosition(CCPoint& position);

	void setTargetPosition(CCPoint& targetPosition);

	void setTouchMove(bool isTouchMove);

	void setDirection(int direction);

	void setDirectionEXT(int directionX, int directionY);

	void setNextDirectionX(int nextDirectionX);

	void setNextDirectionY(int nextDirectionY);

	void setAction(int action);

	void setIsAi(bool isAi);

	void setAI(int aiType, int aiDuration);

	void setStateMachine(StateMachine* stateMachine);
};

#endif
