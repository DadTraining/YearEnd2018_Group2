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
#include"PopUpEndGame.h"

#pragma region declare 
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

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _backGround = cocos2d::Sprite::create(BACKGROUND_IMG);
	_backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//_backGround->setOpacity(0.1);
	addChild(_backGround, -1);

	InfoMap::setScore(0);
	countDownButtonMeat = 1;
	pressed = 0;

	callBackAlive = 0;
	ship = new Ship(this);
	mItem = new Item(this);

	InitShark();
	SetPauseGame();
	ButtonShoot();
	SetItemBox();


	mCable = new Cable(this);
	mCable->GetRect();

	//////////////////////
	RegisterEvent();

	//
	ShowScore();
	////////////
	//loading time
	setTimeLoading();

	Constants::setInMap(false);
	//initPopUpLevelEndGame();

	this->scheduleUpdate();
	return true;
}


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
}

void GamePlayScene::update(float delta)
{

	//	CCLOG("%d", InfoMap::getScore());
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
	mCable->CheckSharkNearCable(sharkList, ship);

	////////////////////////////
	//count down time button meat
	countDownButtonMeat++;
	if (countDownButtonMeat % 300 == 0)
	{
		//setPressWhiteButton(true);
	}
	if (pressed == 1)
	{
		//	setPressWhiteButton(false);
		countDownButtonMeat = 1;
		pressed = 0;
	}

	mCable->Update();


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
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// show popup end game include score and star
		// new class popup next game or goto home

		//PopUpLevelEndGame();
		//showEndGame();
		Constants::ReleaseButton();
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
			mCable->Bitten();
			tag->setIsBitten(false);
			tag->BiteAnimation();
			mCable->EffectCable();

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

void GamePlayScene::showEndGame()
{

	cocos2d::Director::getInstance()->pause();
	/*PopupEndGame *popUpEnd = PopupEndGame::create();
	this->addChild(popUpEnd, 110);
	popUpEnd->getLayer()->setVisible(true);*/
	PopupEndGame *popUpEnd = mListPlayEndGame[InfoMap::getMapLevel()];
	this->addChild(popUpEnd, 110);
	popUpEnd->getLayer()->setVisible(true);
}

void GamePlayScene::ShowScore()
{

	////////////////////////////
	//sprite coin
	auto coin = Sprite::create(COIN);
	coin->setAnchorPoint(Vec2(0, 1));
	coin->setPosition(cocos2d::Vec2(15, btnPause->getPosition().y));
	this->addChild(coin, 5);


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
	mLabelScore->setAnchorPoint(Vec2(0, 1));
	mLabelScore->setPosition(cocos2d::Vec2(coin->getPosition().x + visibleSize.width / 13,
		coin->getPosition().y - 5));
	mLabelScore->enableGlow(Color4B::BLUE);
	this->addChild(mLabelScore, 5);

}

void GamePlayScene::RegisterEvent()
{
	//////////////////////
	//catch event collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto listennerTouch = cocos2d::EventListenerTouchOneByOne::create();
	listennerTouch->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
	listennerTouch->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMoved, this);
	listennerTouch->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnded, this);
	listennerTouch->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listennerTouch, this);
}

void GamePlayScene::ButtonShoot()
{

	auto blueButton = ui::Button::create(BUTTON_BLUE_IMG_NOR);
	blueButton->setAnchorPoint(cocos2d::Vec2(1, 0));
	blueButton->setPosition(cocos2d::Vec2(visibleSize.width - 20, 20));
	blueButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_BLUE);
	});
	addChild(blueButton, 999);

	auto redButton = ui::Button::create(BUTTON_RED_IMG_NOR);
	redButton->setAnchorPoint(cocos2d::Vec2(1, 0));
	redButton->setPosition(cocos2d::Vec2(visibleSize.width - 20, 35 + blueButton->getContentSize().height));
	redButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_RED);
	});
	addChild(redButton, 999);

	auto yellowButton = ui::Button::create(BUTTON_YELLOW_IMG_NOR);
	yellowButton->setAnchorPoint(cocos2d::Vec2(1, 0));
	yellowButton->setPosition(cocos2d::Vec2(visibleSize.width - 40 - blueButton->getContentSize().width, 20));
	yellowButton->addClickEventListener([&](Ref* event) {
		ship->ShootColor(BULLET_SHOOT_YELLOW);
	});
	addChild(yellowButton, 999);
}

void GamePlayScene::SetItemBox()
{
	auto itemBox = Sprite::create(ITEM_BOX);
	/// set position
	itemBox->setAnchorPoint(cocos2d::Vec2(0.2, 0));
	itemBox->setPosition(35, 5);
	itemBox->setOpacity(120);
	addChild(itemBox, 3);
	auto _x = itemBox->getContentSize().width;
	for (int i = 1; i <= 3; i++)
	{
		std::string path = "item/", png = ".png", name;
		char c = '0' + i;
		name = path + c + png;
		auto button = ui::Button::create(name);
		button->setAnchorPoint(cocos2d::Vec2(0, 0));
		listItem.push_back(button);
		switch (i)
		{
		case 1: //brick
			button->setPosition(Vec2(45, itemBox->getPosition().y + 35));
			button->addClickEventListener([=](Ref* event)
			{
				mItem->StunShark(sharkList);
			});
			break;
		case 2: //hp
			button->setPosition(Vec2(_x / 3.5, itemBox->getPosition().y + 27));
			button->addClickEventListener([=](Ref* event)
			{
				mCable->IncreaseHP();
			});
			break;
		case 3: //bomb
			button->setPosition(Vec2((_x * 2 / 4 ), itemBox->getPosition().y + 27));
			button->addClickEventListener([=](Ref* event)
			{
				mItem->KillSharkByBoom(sharkList);
			});
			break;
		}
		this->addChild(button, 4);
	}
}

void GamePlayScene::InitShark()
{
	for (int i = 0; i < SHARK_MAX_ON_SCREEN; i++)
	{
		Shark* s = new Shark(this);
		s->SetTag(i + 1);
		sharkList.push_back(s);
	}
}

void GamePlayScene::SetPauseGame()
{

	btnPause = ui::Button::create(BUTTON_PAUSE_IMG);
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(cocos2d::Vec2(visibleSize.width - 15,
		visibleSize.height * 0.98));
	addChild(btnPause, 99);
	Constants::AddButtonIntoMapLevel(btnPause);
	btnPause->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->pause();
			PopupSetting *popUpSetting = PopupSetting::create();
			this->addChild(popUpSetting, 110);
			popUpSetting->getLayer()->setVisible(true);
			Constants::SetEnableAllTouchEventOnMapLevel(false);
			break;
		}
	});
}

void GamePlayScene::DoClone(Shark * aliveShark)
{
	for (int i = sharkList.size() - 1; i >= 0; i--)
	{
		if (!sharkList[i]->SpriteIsVisible())
		{
			sharkList[i]->Clone(aliveShark);
			//sharkList[i]->SetVisible(true);
			return;
		}
	}
}

Shark * GamePlayScene::SharkAlive(int tag)
{
	for (int i = 0; i < sharkList.size(); i++)
	{
		if (sharkList[i]->GetSprite()->getTag() == tag)
		{
			return sharkList[i];
		}
	}
	return nullptr;
}

/*loading time*/
void GamePlayScene::setTimeLoading()
{
	auto loadingTimeBG = Sprite::create(LOADING_TIME_BG);
	loadingTimeBG->setAnchorPoint(Vec2(1, 0.5));
	loadingTimeBG->setPosition(Vec2(btnPause->getPosition().x - visibleSize.width / 13,
		btnPause->getPosition().y - btnPause->getContentSize().height / 2));
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

		int percent = (int)loadingTime->getPercent();
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
	auto location = touch->getLocation();
	if (
		location.y > Constants::getVisibleSize().height / 5
		&& location.y < Constants::getVisibleSize().height - SHARK_ZONE_TOP
		&& location.x < Constants::getVisibleSize().width / 2
		)
	{
		return true;
	}
	return false;
}

void GamePlayScene::onTouchMoved(Touch * touch, Event * event)
{

}

void GamePlayScene::onTouchEnded(Touch * touch, Event * event)
{
	ship->leftOrRight(ship->GetDirection());
}


bool GamePlayScene::onContactBegin(PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA()->getBody()->getNode();
	auto shapeB = contact.getShapeB()->getBody()->getNode();
	auto objectA = shapeA->getTag();
	auto objectB = shapeB->getTag();
	if (objectA == 0 && objectB != 0 ||
		objectA != 0 && objectB == 0
		)
	{
		//CCLOG("bitten");
		if (objectA != 0)
		{
			CheckColisionSharkWithCable(objectA);
		}
		else
		{
			CheckColisionSharkWithCable(objectB);
		}

	}
	else if (objectA >= 100 && objectB > 0 && objectB < 100 ||
		objectB >= 100 && objectA > 0 && objectA < 100
		)
	{
		bool _result = true;
		if (objectA >= 100)
		{
			_result = ship->Collision(sharkList, objectB, objectA);
			if (!_result)
			{
				//DoClone(SharkAlive(objectB));
				SharkAlive(objectB)->Angry();
			}
		}
		else
		{
			_result = ship->Collision(sharkList, objectA, objectB);
			if (!_result)
			{
				//DoClone(SharkAlive(objectA));
				SharkAlive(objectA)->Angry();
			}
		}
	}
	//CCLOG("game play : colision");
	return false;
}



