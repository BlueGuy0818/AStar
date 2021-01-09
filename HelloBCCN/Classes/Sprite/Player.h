#ifndef __Player__
#define __Player__

#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Sprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
using namespace std;

struct PlayerAttribute
{
	// 武力
	int wuLi;

	// 智力
	int zhiLi;

	// 体力
	int tiLi;

	// 敏捷
	int minJie;

	// 怒气
	int nuQi;

	// 暴击
	int baoJi;

	// 闪避
	int shanBi;

	// 识破
	int shiPo;

	// 命中
	int mingZhong;

	// 格档
	int geDang;

	// 暴击伤害
	int baoJiShangHai;

	// 物理攻击
	int wuLiGongJi;

	// 物理防御
	int wuLiFangYu;

	// 法术攻击
	int faShuGongJi;

	// 法术防御
	int faShuFangYu;

	// 生命
	int shengMing;
};

class Player : public Sprite
{
public:
	Player();
	~Player();

	PlayerAttribute attribute;

	// 全局唯一编号
	int guid;
	// 等级
	int lv;

	void updateEXT(float delta);
};

#endif
