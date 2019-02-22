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
Item * item;

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

	auto static visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	MyBodyParser::getInstance()->parseJsonFile(SHARK_BODY_PARSER);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _backGround = cocos2d::Sprite::create(BACKGROUND_IMG);
	_backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	
	addChild(_backGround, -1);


#pragma region button

	auto whiteButton = ui::Button::create(BUTTON_WHITE_IMG_NOR);
	whiteButton->setPosition(cocos2d::Vec2(visibleSize.width * 9.25 / 10, visibleSize.height * 1.25 / 10));
	whiteButton->addClickEventListener([&](Ref* event) {
		//ship->ShootColor(BULLET_SHOOT_BLACK);
	});
	addChild(whiteButton, 100);

	auto blueButton = ui::Button::create(BUTTON_BLUE_IMG_NOR);
	blueButton->setPosition(cocos2d::Vec2(visibleSize.width * 8 / 10, whiteButton->getPosition().y));
	blueButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_BLUE);
	});
	addChild(blueButton, 100);

	auto redButton = ui::Button::create(BUTTON_RED_IMG_NOR);
	redButton->setPosition(cocos2d::Vec2(visibleSize.width * 5.9 /7, visibleSize.height / 3.75));
	redButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_RED);
	});
	addChild(redButton, 100);

	auto yellowButton = ui::Button::create(BUTTON_YELLOW_IMG_NOR);
	yellowButton->setPosition(cocos2d::Vec2(whiteButton->getPosition().x, visibleSize.height / 3));
	yellowButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_YELLOW);
	});
	addChild(yellowButton, 100);

	////////////////////////
	//left and right button
	auto leftButton = ui::Button::create(BUTTON_LEFT);
	leftButton->setPosition(cocos2d::Vec2(visibleSize.width - whiteButton->getPosition().x, 
							whiteButton->getPosition().y));
	leftButton->addClickEventListener([&](Ref* event) {
		ship->leftOrRight(false);
	});
	addChild(leftButton, 100);

	auto rightButton = ui::Button::create(BUTTON_RIGHT);
	rightButton->setPosition(cocos2d::Vec2(leftButton->getPosition().x + visibleSize.width / 10,
							whiteButton->getPosition().y));
	rightButton->addClickEventListener([&](Ref* event) {
		ship->leftOrRight(true);
	});
	addChild(rightButton, 100);

	auto itemBox = Sprite::create(ITEM_BOX);
	itemBox->setPosition(cocos2d::Vec2(visibleSize.width / 2,
		whiteButton->getPosition().y - visibleSize.height / 50));
	addChild(itemBox, 3);
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

	callBackAlive = 0;
	ship = new Ship(this);
	item = new Item(this);
	for (int i = 1; i <= 3; i++)
	{
		std::string path = "item/", png = ".png", name;
		char c = '0' + i;
		name = path + c + png;
		auto button = ui::Button::create(name);
		listItem.push_back(button);
		switch (i)
		{
		case 1: //brick
			button->setPosition(Vec2(visibleSize.width / 3, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				item->StunShark(sharkList);

			});
			break;

		case 2: //hp
			button->setPosition(Vec2(visibleSize.width / 2, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				item->IncreaseBlood();

			});
			break;

		case 3: //bomb
			button->setPosition(Vec2(visibleSize.width *2 / 3, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				item->KillSharkByBoom(sharkList);
			});
			break;
		default:
			break;
		}
		this->addChild(button, 4);

	}




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
	item->Update();
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
			cable->EffectCable();
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
	auto a = shapeA->getTag();
	auto b = shapeB->getTag();
	if (shapeA->getTag() == 0 && shapeB->getTag() != 0 ||
		shapeA->getTag() != 0 && shapeB->getTag() == 0
		)
	{
		//CCLOG("bitten");
		if (shapeA->getTag() != 0)
		{
			CheckColisionSharkWithCable(shapeA->getTag());
		}
		else
		{
			CheckColisionSharkWithCable(shapeB->getTag());
		}

	}
	else if (shapeA->getTag() >= 100 && shapeB->getTag() > 0 && shapeB->getTag() < 100 ||
		shapeB->getTag() >= 100 && shapeA->getTag() > 0 && shapeA->getTag() < 100
		)
	{
		if (shapeA->getTag() >= 100)
		{
			ship->Collision(sharkList, shapeB->getTag(), shapeA->getTag());
		} 
		else
		{ 
			ship->Collision(sharkList, shapeA->getTag(), shapeB->getTag());
		}
	}
	CCLOG("game play : colision");
	return false;
}

