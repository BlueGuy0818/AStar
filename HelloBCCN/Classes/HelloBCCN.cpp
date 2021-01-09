#include "HelloBCCN.h"
#include "UTF8\utf8vector.h"

#include "tinytab\DataBase.h"
#include "tinytab\DBC_Struct.h"

#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

static HelloBCCN* bccn = NULL;

HelloBCCN* HelloBCCN::getTheOnlyInstance()
{
	if (!bccn)
	{
		bccn = new HelloBCCN();
		bccn->init();
		bccn->autorelease();
	}

	return bccn;
}

CCScene* HelloBCCN::scene()
{
	CCScene* scene = CCScene::create();
	HelloBCCN* layer = HelloBCCN::getTheOnlyInstance();
	scene->addChild(layer);
	return scene;
}

bool HelloBCCN::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CDataBaseSystem::GetMe()->Initial(NULL);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio\\TianXiaDiYi.mp3", true);
	playCgAction();

	mainCityScene = NULL;
	setKeypadEnabled(true);
	scheduleUpdate();

	return true;
}

void HelloBCCN::draw()
{
}

void HelloBCCN::update( float delta )
{
	if (mainCityScene != NULL)
	{
		mainCityScene->updateEXT(delta);
	}
}

bool HelloBCCN::ccTouchBegan( CCTouch* pTouch, CCEvent* event )
{
	return true;
}

void HelloBCCN::ccTouchMoved( CCTouch* pTouch, CCEvent* event )
{

}

void HelloBCCN::ccTouchEnded( CCTouch* pTouch, CCEvent* event )
{

}

void HelloBCCN::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
}

void HelloBCCN::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
	CCLayer::onEnter();
}

void HelloBCCN::onExit()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void HelloBCCN::setSceneType(int type)
{
	this->sceneType = sceneType;
}

long long HelloBCCN::getCurrentTime()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

UIPanel* HelloBCCN::getMultiString(const char* s, int maxLineWidth)
{
	UIPanel* multyStringPanel = UIPanel::create();
	const char* multyStringUTF8 = ansi2utf8(s);

	int lengthUTF8 = strlen(multyStringUTF8);
	utf8vector vector = utf8vector_create(multyStringUTF8, lengthUTF8);

	string utf8Line;
	UILabel* utf8LineTestLabel = UILabel::create();

	wchar_t uni = 0;
	int line = 0;

	while ((uni = utf8vector_next_unichar(vector, utf8Line)) != '\0')
	{
		utf8LineTestLabel->setText(utf8Line.c_str());

		if (utf8LineTestLabel->getContentSize().width > maxLineWidth)
		{
			UILabel* utf8LineLabel = UILabel::create();
			utf8LineLabel->setText((char*)utf8Line.c_str());
			utf8LineLabel->setAnchorPoint(ccp(0, 0.5));
			utf8LineLabel->setPositionY(-line*utf8LineTestLabel->getContentSize().height);
			multyStringPanel->addChild(utf8LineLabel);

			utf8Line.clear();
			line++;
		}
	}

	if (utf8Line.size() != 0)
	{
		UILabel* utf8LineLabel = UILabel::create();
		utf8LineLabel->setText((char*)utf8Line.c_str());
		utf8LineLabel->setAnchorPoint(ccp(0, 0.5));
		utf8LineLabel->setPositionY(-line*utf8LineTestLabel->getContentSize().height);
		multyStringPanel->addChild(utf8LineLabel);
	}

	delete[] multyStringUTF8;
	utf8LineTestLabel->release();
	utf8vector_free(vector);

	return multyStringPanel;
}

char* HelloBCCN::ansi2utf8(const char* inbuf)
{
	iconv_t cd;

	cd = iconv_open("UTF-8", "GBK");

	if (cd == 0)
	{
		return NULL;
	}

	size_t inbytesleft = strlen(inbuf);
	size_t outbytesleft = inbytesleft * 6;
	char* outbuf = new char[outbytesleft];

	const char* in = inbuf;
	char* out = outbuf;

	memset(outbuf, 0, outbytesleft);

	if (iconv(cd, &in, &inbytesleft, &out, &outbytesleft) == -1) 
	{
		delete[] outbuf;
		return NULL;
	}

	iconv_close(cd);
	return outbuf;
}

CCAnimation* animation;
CCAnimate* animate;
CCSequence* sequence;
CCRepeat* repeat;

void HelloBCCN::playCgAction()
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("TianXiaDiYiCg.png");
	CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getPixelsWide(), texture->getPixelsHigh()));
	cgAction = CCSprite::createWithSpriteFrame(frame);
	cgAction->retain();
	cgAction->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	addChild(cgAction);
	CCActionInterval* actionBy = CCSkewBy::create(2, 0.0f, -180.0f);
	CCSequence*  sequence = CCSequence::create(actionBy, NULL);
	cgAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(HelloBCCN::playCgActionCallback)), NULL));
}

void HelloBCCN::playCgActionCallback( CCNode* pSender )
{
	CCTexture2D* tianTexture = CCTextureCache::sharedTextureCache()->addImage("Tian.png");
	CCSpriteFrame* tianFrame = CCSpriteFrame::createWithTexture(tianTexture, CCRectMake(0, 0, tianTexture->getPixelsWide(), tianTexture->getPixelsHigh()));
	tianAction = CCSprite::createWithSpriteFrame(tianFrame);
	tianAction->retain();
	tianAction->setPosition(ccp(visibleSize.width/2, visibleSize.height));
	tianAction->setFlipX(true);
	CCActionInterval* tianActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 + 1.5 * tianTexture->getPixelsHigh()));
	CCActionInterval* tianActionRotate = CCRotateTo::create(0.25, 0, 180);
	CCSequence*  sequence = CCSequence::create(tianActionTo, tianActionRotate, NULL);
	tianAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(HelloBCCN::tianActionCallback)), NULL));
	addChild(tianAction);
}

void HelloBCCN::tianActionCallback( CCNode* pSender )
{
	CCTexture2D* xiaTexture = CCTextureCache::sharedTextureCache()->addImage("Xia.png");
	CCSpriteFrame* xiaFrame = CCSpriteFrame::createWithTexture(xiaTexture, CCRectMake(0, 0, xiaTexture->getPixelsWide(), xiaTexture->getPixelsHigh()));
	xiaAction = CCSprite::createWithSpriteFrame(xiaFrame);
	xiaAction->retain();
	xiaAction->setPosition(ccp(visibleSize.width/2 - visibleSize.width/3, visibleSize.height/2 + xiaTexture->getPixelsHigh()));
	CCActionInterval* xiaActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 + 0.5 * xiaTexture->getPixelsHigh()));
	CCSequence* sequence = CCSequence::create(xiaActionTo, NULL);
	xiaAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(HelloBCCN::xiaActionCallback)), NULL));
	addChild(xiaAction);
}

void HelloBCCN::xiaActionCallback( CCNode* pSender )
{
	CCTexture2D* diTexture = CCTextureCache::sharedTextureCache()->addImage("Di.png");
	CCSpriteFrame* diFrame = CCSpriteFrame::createWithTexture(diTexture, CCRectMake(0, 0, diTexture->getPixelsWide(), diTexture->getPixelsHigh()));
	diAction = CCSprite::createWithSpriteFrame(diFrame);
	diAction->retain();
	diAction->setPosition(ccp(visibleSize.width/2 + visibleSize.width/3,  visibleSize.height/2 - diTexture->getPixelsHigh()));
	CCActionInterval* diActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2, visibleSize.height/2 - 0.5 * diTexture->getPixelsHigh()));
	CCSequence* sequence = CCSequence::create(diActionTo, NULL);
	diAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(HelloBCCN::diActionCallback)), NULL));
	addChild(diAction);
}

void HelloBCCN::diActionCallback( CCNode* pSender )
{
	CCTexture2D* yiTexture = CCTextureCache::sharedTextureCache()->addImage("Yi.png");
	CCSpriteFrame* yiFrame = CCSpriteFrame::createWithTexture(yiTexture, CCRectMake(0, 0, yiTexture->getPixelsWide(), yiTexture->getPixelsHigh()));
	yiAction = CCSprite::createWithSpriteFrame(yiFrame);
	yiAction->retain();
	yiAction->setPosition(ccp(visibleSize.width/2, 0));
	yiAction->setFlipX(true);
	CCActionInterval* yiActionRotate = CCRotateBy::create(0.25, 0, 180);
	CCActionInterval* yiActionTo = CCMoveTo::create(0.5, ccp(visibleSize.width/2,  visibleSize.height/2 - 1.5 * yiTexture->getPixelsHigh()));
	CCActionInterval* yiActionRotate2 = CCRotateTo::create(1, 0, 180);
	CCSequence* sequence = CCSequence::create(yiActionRotate, yiActionTo, yiActionRotate2, NULL);
	yiAction->runAction(CCSequence::create(sequence, CCCallFuncN::create(this, callfuncN_selector(HelloBCCN::yiActionCallback)), NULL));
	addChild(yiAction);
}

void HelloBCCN::yiActionCallback( CCNode* pSender )
{
	cgAction->setVisible(false);
	tianAction->setVisible(false);
	xiaAction->setVisible(false);
	diAction->setVisible(false);
	yiAction->setVisible(false);

	mainCityScene = MainCityScene::create();
	mainCityScene->retain();
	addChild(mainCityScene);
}