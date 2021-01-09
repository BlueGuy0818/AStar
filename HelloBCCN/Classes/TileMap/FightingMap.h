#ifndef __FIGHTING_MAP__
#define __FIGHTING_MAP__

#include <string>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

class FightingMap
{
public:
	FightingMap();
	~FightingMap();

	CCTMXTiledMap* tiledMap;
	CCPoint position;

	void updateEXT(float delta);

	CCTMXTiledMap* getTMXTiledMap();
};

#endif // __HELLOWORLD_SCENE_H__
