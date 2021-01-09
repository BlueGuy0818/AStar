#include "MainCityScene.h"
#include "AI\StateMachine.h"
#include "Input\Input.h"
#include "AI\PathFind.h"

MainCityScene::MainCityScene()
{
}

MainCityScene::~MainCityScene()
{
	removeChild(mainCity->tiledMap, true);
	removeChild(player->armature, true);
}

bool MainCityScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	mainCity = new MainCity();
	mainCity->tiledMap->setPosition(ccp(0, 0));
	addChild(mainCity->tiledMap);

	player = new Player();
	player->setPosition(ccp(450, 360));
	player->armature->setPosition(ccp(450, 360));
	addChild(player->armature);

	player->setMainCity(mainCity);
	StateMachine* stateMachine = new StateMachine(player);
	player->setStateMachine(stateMachine);

	setKeypadEnabled(true);

	return true;
}

void MainCityScene::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	CCLayer::onEnter();
}

void MainCityScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool MainCityScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocation();

	touchPoint.x = (touchPoint.x - mainCity->position.x);
	touchPoint.y = (touchPoint.y - mainCity->position.y);

	int startX = player->position.x / mainCity->tiledMap->getTileSize().width;
    int startY = (mainCity->tiledMap->getContentSize().height - player->position.y) / mainCity->tiledMap->getTileSize().height;

	int endX = touchPoint.x / mainCity->tiledMap->getTileSize().width;
    int endY = (mainCity->tiledMap->getContentSize().height - touchPoint.y) / mainCity->tiledMap->getTileSize().height;

	// ËÑË÷Â·¾¶
	if (PathFind::getTheOnlyInstance()->AStarSearch(mainCity->tiledMap, startX, startY, endX, endY))
	{
		list<CCPoint>& astarPathList = PathFind::getTheOnlyInstance()->astarPathList;
		list<CCPoint>::iterator it = astarPathList.begin();
		CCTMXLayer* mapLayer = mainCity->tiledMap->layerNamed("mainCityLayer");
		
		CCPoint targetPosition;
		targetPosition.x = (*it).x * mainCity->tiledMap->getTileSize().width + mainCity->tiledMap->getTileSize().width / 2;
		targetPosition.y = mainCity->tiledMap->getContentSize().height - (*it).y * mainCity->tiledMap->getTileSize().height - mainCity->tiledMap->getTileSize().height / 2;
		astarPathList.pop_front();

		player->isAstar = true;
		player->setTargetPosition(targetPosition);
		player->setTouchMove(true);
		player->stateMachine->changeState(WALK);
	}
	
	return true;
}

void MainCityScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void MainCityScene::draw()
{
}

void MainCityScene::updateEXT(float delta)
{
	Input::update();
	mainCity->updateEXT(delta);
	player->updateEXT(delta);
}