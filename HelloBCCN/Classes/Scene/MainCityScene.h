#ifndef __MAIN_CITY_SCENE_H__
#define __MAIN_CITY_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

#include "TileMap\MainCity.h"
#include "Sprite\Player.h"
#include "AI\States.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

using namespace std;

class MainCityScene : public CCLayer
{
public:
	MainCityScene();
	~MainCityScene();
public:

	CCSize visibleSize;
	MainCity* mainCity;

	Player* player;

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	CREATE_FUNC(MainCityScene);

	void draw();

	void updateEXT(float delta);
};

#endif __MAIN_CITY_SCENE_H__