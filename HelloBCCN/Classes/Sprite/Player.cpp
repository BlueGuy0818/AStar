#include "Player.h"
#include "AI\States.h"
#include "AI\SpriteStates.h"

Player::Player()
{
	guid = 10086;
	lv = 10;

	memset(&attribute, 0, sizeof(attribute));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("HeroAnimation0.png", "HeroAnimation0.plist", "HeroAnimation.ExportJson");;
	armature = CCArmature::create("HeroAnimation");

	shadowSprite = CCSprite::create("shadow.png");

	shadowSprite->setAnchorPoint(ccp(0.5, 1));
	shadowSprite->setPositionY(-50);
	armature->addChild(shadowSprite);

	direction = RIGHT;
	face = RIGHT;

	setType(PLAYER);
	setAction(STAND);
}

Player::~Player()
{
}

void Player::updateEXT(float delta)
{
	Sprite::updateEXT(delta);
}