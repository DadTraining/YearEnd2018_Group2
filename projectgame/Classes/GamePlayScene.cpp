#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Shark.h"
#include "Meat.h"
#include <vector>
#include "define.h"	
#include "Constants.h"
#include "MyBodyParser.h"
#include "ui\UIButton.h"
#include"PopUpPlay.h"
#include"PopUpPause.h"
#include"PopUpSetting.h"
#include "InfoMap.h"
#include "MapScene.h"



USING_NS_CC;


#pragma region Shark
Item* mItem;
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
	

	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	MyBodyParser::getInstance()->parseJsonFile(SHARK_BODY_PARSER);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _backGround = cocos2d::Sprite::create(BACKGROUND_IMG);
	_backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//_backGround->setOpacity(0.1);
	addChild(_backGround, -1);
	
	countDownButtonMeat = 1;
	pressed = 0;
	
	////////////////////////////////////////////////////
	//setting and pause button
	btnSettingScene = ui::Button::create(BUTTON_SETTING_IMG);
	btnSettingScene->setAnchorPoint(Vec2(1, 1));
	btnSettingScene->setPosition(cocos2d::Vec2(visibleSize.width - 15, visibleSize.height - 30));
	addChild(btnSettingScene);
	btnSettingScene->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->pause();
			PopupSetting *popUpSetting = PopupSetting::create();
			this->addChild(popUpSetting, 110);
			popUpSetting->getLayer()->setVisible(true);
			break;
		}
	});

	btnPause = ui::Button::create(BUTTON_PAUSE_IMG);
	btnSettingScene->setAnchorPoint(Vec2(1, 0.5));
	btnPause->setPosition(cocos2d::Vec2(btnSettingScene->getPosition().x 
		- btnSettingScene->getContentSize().width - 35, 
		btnSettingScene->getPosition().y ));
	addChild(btnPause);
	btnPause->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//this->unscheduleUpdate();
			cocos2d::Director::getInstance()->pause();
			PopupPause *popUpPause = PopupPause::create();
			this->addChild(popUpPause, 110);
			/*deleteShark();*/
			popUpPause->getLayer()->setVisible(true);
			break;
		}
	});
	

	whiteButton = ui::Button::create(BUTTON_WHITE_IMG_NOR, BUTTON_WHITE_IMG_PRE, BUTTON_BLACK_IMG_NOR);
	whiteButton->setPosition(cocos2d::Vec2(visibleSize.width * 9.25 / 10, visibleSize.height * 1.25 / 10));
	whiteButton->addClickEventListener([&](Ref* event) {
		initMeatList(this, sharkList);
		pressed = 1;
	});
	addChild(whiteButton, 100);
	setPressWhiteButton(false);

	auto blueButton = ui::Button::create(BUTTON_BLUE_IMG_NOR);
	blueButton->setPosition(cocos2d::Vec2(visibleSize.width * 8.32 / 10, whiteButton->getPosition().y));
	blueButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_BLUE);
	});
	addChild(blueButton, 999);

	auto redButton = ui::Button::create(BUTTON_RED_IMG_NOR);
	redButton->setPosition(cocos2d::Vec2(visibleSize.width * 5.95 / 7, visibleSize.height / 3.84));
	redButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_RED);
	});
	addChild(redButton, 999);

	auto yellowButton = ui::Button::create(BUTTON_YELLOW_IMG_NOR);
	yellowButton->setPosition(cocos2d::Vec2(whiteButton->getPosition().x, visibleSize.height / 3.5));
	yellowButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_YELLOW);
	});
	addChild(yellowButton, 999);

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
	///// end

	auto itemBox = Sprite::create(ITEM_BOX);
	itemBox->setPosition(cocos2d::Vec2(visibleSize.width / 2,
		whiteButton->getPosition().y - visibleSize.height / 50));
	itemBox->setOpacity(120);
	addChild(itemBox, 3);

	////////////////////////////
	//sprite coin
	auto coin = Sprite::create(COIN);
	coin->setAnchorPoint(Vec2(0, 0.5));
	coin->setPosition(cocos2d::Vec2(15, btnSettingScene->getPosition().y));
	this->addChild(coin, 5);

#pragma endregion

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	callBackAlive = 0;
	ship = new Ship(this);
	//ship->SetVisible(false);
	mItem = new Item(this);

	for (int i = 0; i < SHARK_MAX_ON_SCREEN; i++)
	{
		Shark* s = new Shark(this);
		s->SetTag(i + 1);
		sharkList.push_back(s);
	}


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
			button->setPosition(Vec2(visibleSize.width / 2.5, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				mItem->StunShark(sharkList);

			});
			break;

		case 2: //hp
			button->setPosition(Vec2(visibleSize.width / 2, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				//item->IncreaseBlood();

			});
			break;

		case 3: //bomb
			button->setPosition(Vec2(visibleSize.width *2 / 3.35, itemBox->getPosition().y));
			button->addClickEventListener([=](Ref* event)
			{
				mItem->KillSharkByBoom(sharkList);
			});
			break;
		default:
			break;
		}
		this->addChild(button, 4);

	}

	cable = new Cable(this);
	cable->GetRect();

	//////////////////////
	//catch event collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//InfoMap::setScore(0);

	this->scheduleUpdate();
	mScore = InfoMap::getScore();

	///////////////////////////////
	//label score
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT_SCORE;
	labelConfig.fontSize = 31;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 2;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	mLabelScore = Label::createWithTTF(labelConfig, std::to_string(mScore));
	mLabelScore->setPosition(cocos2d::Vec2(coin->getPosition().x + visibleSize.width / 13,
							coin->getPosition().y - 5));
	mLabelScore->enableGlow(Color4B::BLUE);
	this->addChild(mLabelScore, 5);

	////////////
	//loading time
	setTimeLoading();

	Constants::setInMap(false);
	return true;
}


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
}

void GamePlayScene::update(float delta)
{
	
	CCLOG("%d", InfoMap::getScore());
	mLabelScore->setString(std::to_string(InfoMap::getScore()));

	/////////////////////
	//count down time meat appear and disappear
	countDownMeat++;
	meatDeleted();
	if (countDownMeat % 140 == 0)
	{
		countDownMeat = 1;
		meatDone();
	}

	//////////////////////
	//update shark
	for (int i = 0; i < sharkList.size(); i++)
	{
		if (sharkList[i]->IsVisible() && sharkList.at(i) != nullptr)
		{
			sharkList[i]->Update();
		}
		else if (sharkList[i]->GetSprite()->isVisible())
		{
			sharkList[i]->Update();
		}
		
	}
	ship->Update();
	mItem->Update();
	cable->CheckSharkNearCable(sharkList, ship);
	
	////////////////////////////
	//count down time button meat
	countDownButtonMeat++;
	if (countDownButtonMeat % 300 == 0)
	{
		setPressWhiteButton(true);
	}
	if (pressed == 1)
	{
		setPressWhiteButton(false);
		countDownButtonMeat = 1;
		pressed = 0;
	}
}

void GamePlayScene::SharkAliveCallBack(int phase)
{
	int size = 0;
	switch (phase)
	{
	case 1:
		size = (int)InfoMap::getPhase1();
		break;
	case 2:
		size = (int)InfoMap::getPhase2();
		break;
	case 3:
		size = (int)InfoMap::getPhase3();
		break;
	default:
		//end game
		//cocos2d::Director::getInstance()->pause();
		this->unscheduleUpdate();

		// show popup end game include score and star
		// new class popup next game or goto home
		
		WinGame();
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1, MapScene::createScene()));
		break;
	}
	
	for (int i = 0; i < size; i++)
	{
		auto x = sharkList[i]->SpriteIsVisible();
		if (!x)
		{
			
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

void GamePlayScene::WinGame()
{
	meatDone();
	Constants::EndGame(InfoMap::getMapLevel(), 1, true, InfoMap::getScore());
	InfoMap::setScore(0);
}

void GamePlayScene::initMeatList(Scene *scene, std::vector<Shark*> sharkList)
{
	countDownMeat = 1;
	for (int i = 0; i < cocos2d::RandomHelper::random_int(1, SHARK_MAX_ON_SCREEN); i++)
	{
		Meat *meat = new Meat(this);
		meat->setPosForMeat(sharkList[i]);
		meatList.push_back(meat);
		if (sharkList[i]->IsVisible())
		{
			meatList[i]->setVisible(true);
		}
	}

	for (int i = 0; i < meatList.size(); i++)
	{
		if (meatList[i]->IsVisible())
		{
			meatList[i]->isEaten(sharkList[i]);
		}
	}
}

void GamePlayScene::meatDone()
{
	for (int i = 0; i < meatList.size(); i++)
	{
		if (meatList[i]->IsVisible())
		{
			meatList[i]->disappear();
			delete(meatList[i]);
			sharkList[i]->SetOldStatus();
			
			sharkList[i]->SwimAnimation();
		}
	}

	meatList.clear();
}

void GamePlayScene::meatDeleted()
{
	for (int i = 0; i < meatList.size(); i++)
	{
		if (meatList[i]->IsVisible() && !sharkList[i]->IsAlive())
		{
			meatList[i]->disappear();
		}
	}
}

void GamePlayScene::setPressWhiteButton(bool pres)
{
	whiteButton->setTouchEnabled(pres);
	whiteButton->setBright(pres);
	whiteButton->setEnabled(pres);
}

/*loading time*/
void GamePlayScene::setTimeLoading()
{
	auto loadingTimeBG = Sprite::create(LOADING_TIME_BG);
	loadingTimeBG->setAnchorPoint(Vec2(1, 0.5));
	loadingTimeBG->setPosition(Vec2(btnPause->getPosition().x - 70,
		btnPause->getPosition().y));
	this->addChild(loadingTimeBG, 99);

	auto loadingTime = ui::LoadingBar::create(LOADING_TIME);
	loadingTime->setAnchorPoint(Vec2(1, 0.5));
	loadingTime->setPercent(0);
	loadingTime->setPosition(loadingTimeBG->getPosition());
	this->addChild(loadingTime, 99);

	auto clock = Sprite::create(TIME);
	clock->setPosition(Vec2(loadingTimeBG->getPosition().x - loadingTimeBG->getContentSize().width
		, loadingTimeBG->getPosition().y));
	this->addChild(clock, 100);

	auto updateLoadingBar = CallFunc::create([=]() {

		int percent = (int) loadingTime->getPercent();
		clock->setPosition(Vec2(clock->getPosition().x + loadingTimeBG->getContentSize().width / 100
			, clock->getPosition().y));
		if (loadingTime->getPercent() < 100)
		{
			loadingTime->setPercent(loadingTime->getPercent() + 1);
		}

		if (loadingTime->getPercent() <= 33)
		{
			SharkAliveCallBack(1);
		}

		if (loadingTime->getPercent() > 33 && loadingTime->getPercent() <= 66)
		{
			SharkAliveCallBack(2);
		}

		if (loadingTime->getPercent() > 66 && loadingTime->getPercent() <= 99)
		{
			SharkAliveCallBack(3);
		}

		if (loadingTime->getPercent() == 100)
		{
			SharkAliveCallBack(4);
		}
	});

	auto sequenceRunUpdateLoadingBar = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.45f));
	auto repeatLoad = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	loadingTime->runAction(repeatLoad);
}

void GamePlayScene::LoseGame()
{

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



