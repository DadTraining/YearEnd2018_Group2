#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Shark.h"
#include <vector>
#include "define.h"	
#include "Constants.h"
#include "MyBodyParser.h"
USING_NS_CC;


#pragma region Shark
std::vector<Shark*> sharkList;
int callBackAlive;
Shark* sk;
cocos2d::Sprite* bluebutton;
cocos2d::Sprite* redbutton;
cocos2d::Sprite* yellowbutton;
cocos2d::Sprite* blackbutton;

#pragma endregion


Scene* GamePlayScene::createScene()
{
	auto scene = cocos2d::Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GamePlayScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	MyBodyParser::getInstance()->parseJsonFile(SHARK_BODY_PARSER);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _backGround = cocos2d::Sprite::create(BACKGROUND_IMG);
	_backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//_backGround->setScaleY(Constants::getVisibleSize().height / _backGround->getContentSize().height);
	//_backGround->setScaleX(Constants::getVisibleSize().width / _backGround->getContentSize().width);

	addChild(_backGround, -1);

	auto _cable = cocos2d::Sprite::create(CABLE_IMG);
	_cable->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_cable->setScaleY(Constants::setScaleSprite(Constants::getVisibleSize().height, 1, _cable->getContentSize().height));
	addChild(_cable, 1);

#pragma region button

	yellowbutton = cocos2d::Sprite::create(BUTTON_YELLOW_IMG);
	yellowbutton->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 7));
	//yellowbutton->setScale(Constants::setScaleSprite(Constants::getVisibleSize().height, 6, yellowbutton->getContentSize().height));
	addChild(yellowbutton, 137);

	bluebutton = cocos2d::Sprite::create(BUTTON_BLUE_IMG);
	bluebutton->setPosition(cocos2d::Vec2(visibleSize.width * 2 / 5, visibleSize.height / 7));
	//bluebutton->setScale(Constants::setScaleSprite(Constants::getVisibleSize().height, 6, bluebutton->getContentSize().height));
	addChild(bluebutton, 137);

	redbutton = cocos2d::Sprite::create(BUTTON_RED_IMG);
	redbutton->setPosition(cocos2d::Vec2(visibleSize.width * 3 / 5, visibleSize.height / 7));
	//redbutton->setScale(Constants::setScaleSprite(Constants::getVisibleSize().height, 6, redbutton->getContentSize().height));
	addChild(redbutton, 137);

	blackbutton = cocos2d::Sprite::create(BUTTON_BLACK_IMG);
	blackbutton->setPosition(cocos2d::Vec2(visibleSize.width * 4 / 5, visibleSize.height / 7));
	//blackbutton->setScale(Constants::setScaleSprite(Constants::getVisibleSize().height, 6, blackbutton->getContentSize().height));
	addChild(blackbutton, 137);

#pragma endregion

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	for (int i = 0; i < SHARK_MAX_ON_SCREEN; i++)
	{
		sharkList.push_back(new Shark(this));
	}
	sk = new Shark(this);
	sk->SetVisible(true);

	auto listenerButton = EventListenerTouchOneByOne::create();
	listenerButton->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerButton, this);

	callBackAlive = 0;
	ship = new Ship(this);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	return true;
	//
}


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
}

void GamePlayScene::update(float delta)
{
	//	sk->Update();
	callBackAlive += 1;
	if (callBackAlive % SHARK_CALL_BACK_ALIVE == 0)
	{
		GamePlayScene::SharkAliveCallBack();
	}

	for (int i = 0; i < sharkList.size(); i++)
	{
		if (sharkList[i]->IsVisible())
		{
			sharkList[i]->Update();
		}
	}
	ship->Update();
	//	ship->Collision(sharkList);
}

void GamePlayScene::SharkAliveCallBack()
{
	for (int i = 0; i < sharkList.size(); i++)
	{
		auto x = sharkList[i]->SpriteIsVisible();
		if (!x)
		{
			//sharkList[i]->SetVisible(true);
			sharkList[i]->Init();
			break;
		}
	}
}

bool GamePlayScene::onTouchBegan(Touch * touch, Event * event)
{
	auto localTouch = touch->getLocation();

	if (bluebutton->getBoundingBox().containsPoint(localTouch))
	{
		ship->ShootColor(BULLET_SHOOT_BLUE);
	}
	else if (yellowbutton->getBoundingBox().containsPoint(localTouch))
	{
		ship->ShootColor(BULLET_SHOOT_YELLOW);

	}
	else if (blackbutton->getBoundingBox().containsPoint(localTouch))
	{
		ship->ShootColor(BULLET_SHOOT_BLACK);

	}
	else if (redbutton->getBoundingBox().containsPoint(localTouch))
	{
		ship->ShootColor(BULLET_SHOOT_RED);
	}
	return false;
}


bool GamePlayScene::onContactBegin(PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();
	auto a = shapeA->getCollisionBitmask();
	auto b = shapeB->getCollisionBitmask();
	if (a != b)
	{
		ship->Collision(sharkList);
	}
	return true;
}

