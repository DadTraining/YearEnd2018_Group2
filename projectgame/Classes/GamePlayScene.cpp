#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Shark.h"
#include <vector>
#include "define.h"	
#include "Constants.h"
#include "MyBodyParser.h"
#include "ui\UIButton.h"
USING_NS_CC;


#pragma region Shark
std::vector<Shark*> sharkList;
int callBackAlive;
Shark* sk;
#pragma endregion


Scene* GamePlayScene::createScene()
{
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

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

	/*auto _cable = cocos2d::Sprite::create(CABLE_IMG);
	_cable->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_cable->setScaleY(Constants::setScaleSprite(Constants::getVisibleSize().height,1,_cable->getContentSize().height));
	addChild(_cable, 1);*/


#pragma region button

	auto blueButton = ui::Button::create(BUTTON_BLUE_IMG_NOR, BUTTON_BLUE_IMG_PRESS);
	blueButton->setPosition(cocos2d::Vec2(visibleSize.width * 2 / 10, visibleSize.height * 1.5 / 10));
	blueButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_BLUE);
	});
	addChild(blueButton,100);

	auto redButton = ui::Button::create(BUTTON_RED_IMG_NOR, BUTTON_RED_IMG_PRESS);
	redButton->setPosition(cocos2d::Vec2(visibleSize.width * 4 / 10, visibleSize.height * 1.5 / 10));
	redButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_RED);
	});
	addChild(redButton,100);

	auto yellowButton = ui::Button::create(BUTTON_YELLOW_IMG_NOR, BUTTON_YELLOW_IMG_PRESS);
	yellowButton->setPosition(cocos2d::Vec2(visibleSize.width * 6 / 10, visibleSize.height * 1.5 / 10));
	yellowButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_YELLOW);
	});
	addChild(yellowButton,100);

	auto blackButton = ui::Button::create(BUTTON_BLACK_IMG_NOR, BUTTON_BLACK_IMG_PRESS);
	blackButton->setPosition(cocos2d::Vec2(visibleSize.width * 8 / 10, visibleSize.height * 1.5 / 10));
	blackButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_BLACK);
	});
	addChild(blackButton,100);
#pragma endregion

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	for (int i = 0; i < SHARK_MAX_ON_SCREEN; i++)
	{
		Shark* s = new Shark(this);
		s->SetTag(1 + i);
		sharkList.push_back(s);
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

	cable = new Cable(this);
	cable->GetRect();

	this->scheduleUpdate();

	return true;
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
	//cable->Update();


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

bool GamePlayScene::CheckColisionSharkWithCable(int sharkTag)
{
	for (int i = 0; i < sharkList.size(); i++)
	{
		auto tag = sharkList[i];
		if (tag->GetSprite()->getTag() == sharkTag && tag->IsBitten())
		{
			cable->Bitten();
			tag->setIsBitten(false);
			tag->BiteAnimation();
		}
	}
	return false;
}


bool GamePlayScene::onTouchBegan(Touch * touch, Event * event)
{
	
	return false;
}


bool GamePlayScene::onContactBegin(PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA()->getBody()->getNode();
	auto shapeB = contact.getShapeB()->getBody()->getNode();
	/*auto a = shapeA->getCollisionBitmask();
	auto b = shapeB->getCollisionBitmask();*/
	if (shapeA->getTag()== 0 && shapeB->getTag() !=0 ||
		shapeA->getTag() != 0 && shapeB->getTag() == 0
		)
	{
		CCLOG("bitten");
		if (shapeA->getTag() != 0)
		{
			CheckColisionSharkWithCable(shapeA->getTag());
		}
		else
		{
			CheckColisionSharkWithCable(shapeB->getTag());
		}
		
	}
	else 
	{
		/*CCLOG("bitte");
		ship->Collision(sharkList);*/
	}
	return false;
}

