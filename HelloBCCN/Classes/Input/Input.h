#ifndef __INPUT__
#define __INPUT__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include <windows.h> 
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0) 
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1) 
#endif

class Input
{
public:
	static void update();
};

#endif