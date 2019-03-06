#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Shark.h"
#include "Meat.h"
#include <vector>
#include "define.h"	
#include "Constants.h"
#include "MyBodyParser.h"
#include "ui\UIButton.h"
#include "PopUpPlay.h"
#include "PopUpPause.h"
#include "PopUpSetting.h"
#include "InfoMap.h"
#include "MapScene.h"
#include"PopUpEndGame.h"
#include"PopUpLoseGame.h"

#pragma region declare 
#pragma endregion

Scene* GamePlayScene::createScene()
{
	auto scene = cocos2d::Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GamePlayScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	scene->setTag(333);
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

	//pause = false;

	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	MyBodyParser::getInstance()->parseJsonFile(SHARK_BODY_PARSER);

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	RandomBackGround();

	InfoMap::setScore(0);
	countDownButtonMeat = 1;
	pressed = 0;
	mSharksSkin = InfoMap::getSharkSkin();
	callBackAlive = 0;
	ship = new Ship(this);
	mItem = new Item(this);
	Constants::RefreshItem();
	InitShark();
	SetPauseGame();
	ButtonShoot();
	SetItemBox();

	mCable = new Cable(this);
	mCable->GetRect();

	//////////////////////
	RegisterEvent();

	/////

	//
	ShowScore();
	//
	ShowLevel();
	////////////
	//loading time
	countDownTime = 0;
	setTimeLoading();



	Constants::setInMap(false);
	//initPopUpLevelEndGame();

	/////////
	setCountItem();

	this->scheduleUpdate();

	return true;
}


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
}

void GamePlayScene::update(float delta)
{
	callBackAlive += 1;
	if (mCable->GetHP() <= 0)
	{
		LoseGame();
	}
	//	CCLOG("%d", InfoMap::getScore());
	mLabelScore->setString(std::to_string(InfoMap::getScore()));
	mLabelCountBrick->setString(std::to_string(Constants::GetBricks()));
	mCountHP->setString(std::to_string(Constants::GetHps()));
	mCountGunE->setString(std::to_string(Constants::GetBooms()));
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

	///////////////////////////////
	//count down time loading
	countDownTime++;
	if (countDownTime % FPS == 0)
	{
		float percent = (float)20 / 9;
		loadingTime->setPercent(loadingTime->getPercent() + percent);

		clock->setPosition(Vec2(clock->getPosition().x + loadingTimeBG->getContentSize().width / 45
			, clock->getPosition().y));
	}

	if (countDownTime < 600)
	{
		SharkAliveCallBack(1);
	}

	else if (countDownTime < 1200)
	{
		SharkAliveCallBack(2);
	}

	else if (countDownTime < 1800)
	{
		SharkAliveCallBack(3);
	}

	if (countDownTime >= 1800)
	{
		countDownTime = 0;
		SharkAliveCallBack(4);
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
		WinGame();
		break;
	}

	if (callBackAlive % 40 == 0)
	{
		for (int i = 0; i < size; i++)
		{
			auto x = sharkList[i]->SpriteIsVisible();
			if (!x)
			{
				if (mSharksSkin > 0 && phase != 1)
				{

					int rand = cocos2d::random(1, 10);
					if (InfoMap::getMapLevel() <= 9 && rand <= 7)
					{
						sharkList[i]->SetNumSkinForShark(1);
						sharkList[i]->Init();
					}
					else if (InfoMap::getMapLevel() > 9 && rand <= 4)
					{
						sharkList[i]->SetNumSkinForShark(1);
						sharkList[i]->Init();
					}
					else
					{
						sharkList[i]->SetNumSkinForShark(2);
						sharkList[i]->Init();
						mSharksSkin -= 1;
					}
				}
				else
				{
					sharkList[i]->SetNumSkinForShark(1);
					sharkList[i]->Init();
				}
				break;
			}
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
	if (mCable->GetHP() > 0)
	{
		this->unscheduleUpdate();
		showEndGame();
		InfoMap::setScore(0);
	}
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
			sharkList[i]->CallBackStatus();

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
	// initLevelEndGame();
	PopupEndGame* popup = PopupEndGame::create();

	popup->getLayer()->setVisible(true);
	Constants::SetEnableAllTouchEventOnMapLevel(false);
	int star = 0;
	auto score = InfoMap::getScore();
	if (InfoMap::getScore() > 400)
	{
		star = 3;
	}
	else if (InfoMap::getScore() > 200)
	{
		star = 2;
	}
	else
	{
		star = 1;
	}
	Constants::EndGame(InfoMap::getMapLevel(), star, true, InfoMap::getScore());
	popup->SetLevel(InfoMap::getMapLevel(), star);
	this->addChild(popup, 999);

}

void GamePlayScene::ShowScore()
{

	////////////////////////////
	//sprite coin
	auto coin = Sprite::create(COIN);
	coin->setAnchorPoint(Vec2(0, 1));
	coin->setPosition(cocos2d::Vec2(visibleSize.width / 4, btnPause->getPosition().y));
	this->addChild(coin, 999);

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
	mLabelScore->setPosition(cocos2d::Vec2(coin->getPosition().x + coin->getContentSize().width + 10,
		coin->getPosition().y - 10));
	mLabelScore->setAlignment(cocos2d::TextHAlignment::RIGHT);

	mLabelScore->enableGlow(Color4B::BLUE);
	this->addChild(mLabelScore, 999);

}

void GamePlayScene::ShowLevel()
{
	////////////////////////////
	//sprite coin
	auto level = Sprite::create(LEVEL);
	level->setAnchorPoint(Vec2(0, 1));
	level->setPosition(visibleSize.width*0.02, btnPause->getPosition().y);
	this->addChild(level, 5);


	mLevel = InfoMap::getMapLevel();

	///////////////////////////////
	//label level
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT_LEVEL;
	labelConfig.fontSize = 65;

	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 2;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	mLabelLevel = Label::createWithTTF(labelConfig, std::to_string(mLevel));
	mLabelLevel->setColor(Color3B::WHITE);
	mLabelLevel->setAnchorPoint(Vec2(0, 1));
	mLabelLevel->setPosition(cocos2d::Vec2(level->getPosition().x + visibleSize.width / 8.5,
		level->getPosition().y*1.015));
	mLabelLevel->enableGlow(Color4B::BLUE);
	this->addChild(mLabelLevel, 5);
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
		if (Constants::getOnSFX())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON_BULLET, false);
		}
		ship->ShootColor(BULLET_SHOOT_BLUE);
	});
	addChild(blueButton, 999);

	auto redButton = ui::Button::create(BUTTON_RED_IMG_NOR);
	redButton->setAnchorPoint(cocos2d::Vec2(1, 0));
	redButton->setPosition(cocos2d::Vec2(visibleSize.width - 20, 35 + blueButton->getContentSize().height));
	redButton->addClickEventListener([&](Ref* event) {
		if (Constants::getOnSFX())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON_BULLET, false);
		}
		ship->ShootColor(BULLET_SHOOT_RED);
	});
	addChild(redButton, 999);

	auto yellowButton = ui::Button::create(BUTTON_YELLOW_IMG_NOR);
	yellowButton->setAnchorPoint(cocos2d::Vec2(1, 0));
	yellowButton->setPosition(cocos2d::Vec2(visibleSize.width - 40 - blueButton->getContentSize().width, 20));
	yellowButton->addClickEventListener([&](Ref* event) {
		if (Constants::getOnSFX())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON_BULLET, false);
		}
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
	itemBox->setOpacity(140);
	addChild(itemBox, 3);
	auto _x = itemBox->getContentSize().width;
	for (int i = 1; i <= 3; i++)
	{
		std::string path = "item/", png = ".png", name, _disName;
		char c = '0' + i;
		name = path + c + png;
		_disName = path + c + "." + c + png;
		auto button = ui::Button::create(name, name, _disName);

		button->setAnchorPoint(cocos2d::Vec2(0, 0));
		listItem.push_back(button);
		switch (i)
		{
		case 1: //brick
			button->setPosition(Vec2(45, itemBox->getPosition().y + 25));
			if (Constants::GetBricks() <= 0)
			{
				button->setEnabled(false);
			}
			button->addClickEventListener([=](Ref* event)
			{
				if (!mItem->StunShark(sharkList))
				{
					button->setEnabled(false);
				}
			});
			break;
		case 2: //hp
			button->setPosition(Vec2(_x / 3.5, itemBox->getPosition().y + 25));
			if (Constants::GetHps() <= 0)
			{
				button->setEnabled(false);
			}
			button->addClickEventListener([=](Ref* event)
			{
				if (!mCable->IncreaseHP())
				{
					button->setEnabled(false);
				}
			});
			break;
		case 3: //bomb
			button->setPosition(Vec2((_x * 2 / 4), itemBox->getPosition().y + 25));
			if (Constants::GetBooms() <= 0)
			{
				button->setEnabled(false);
			}
			button->addClickEventListener([=](Ref* event)
			{
				if (!mItem->KillSharkByBoom(sharkList))
				{
					button->setEnabled(false);
				}
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
			if (Constants::getOnSFX())
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON, false);
			}
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

void GamePlayScene::RandomBackGround()
{
	cocos2d::Sprite* _backGround;
	auto _id = cocos2d::random(1, 3);
	switch (_id)
	{
	case 1:
		_backGround = cocos2d::Sprite::create(BACKGROUND_IMG_1);
		break;
	case 2:
		_backGround = cocos2d::Sprite::create(BACKGROUND_IMG_2);

		break;
	case 3:
		_backGround = cocos2d::Sprite::create(BACKGROUND_IMG_3);

		break;
	default:
		_backGround = cocos2d::Sprite::create(BACKGROUND_IMG_1);
		break;
	}
	_backGround->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//_backGround->setOpacity(0.1);
	addChild(_backGround, -1);
}

void GamePlayScene::DoClone(Shark * aliveShark)
{
	for (int i = sharkList.size() - 1; i >= 0; i--)
	{
		if (!sharkList[i]->SpriteIsVisible())
		{
			sharkList[i]->Clone(aliveShark);
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
	loadingTimeBG = Sprite::create(LOADING_TIME_BG);
	loadingTimeBG->setAnchorPoint(Vec2(1, 0.5));
	loadingTimeBG->setPosition(Vec2(btnPause->getPosition().x - visibleSize.width / 13,
		btnPause->getPosition().y - btnPause->getContentSize().height / 2));
	this->addChild(loadingTimeBG, 998);

	loadingTime = ui::LoadingBar::create(LOADING_TIME);
	loadingTime->setPercent(0);
	loadingTime->setAnchorPoint(Vec2(1, 0.5));
	loadingTime->setPosition(loadingTimeBG->getPosition());
	this->addChild(loadingTime, 998);

	auto mark1 = cocos2d::Sprite::create(SHARK_MARK);
	mark1->setPosition(Vec2(
		loadingTime->getPosition().x - loadingTime->getContentSize().width / 3,
		loadingTime->getPosition().y
	));
	this->addChild(mark1, 999);

	auto mark2 = cocos2d::Sprite::create(SHARK_MARK);
	mark2->setPosition(Vec2(
		loadingTime->getPosition().x - loadingTime->getContentSize().width * 2 / 3,
		loadingTime->getPosition().y
	));
	this->addChild(mark2, 999);

	clock = Sprite::create(TIME);
	clock->setPosition(Vec2(loadingTimeBG->getPosition().x - loadingTimeBG->getContentSize().width
		, loadingTimeBG->getPosition().y));
	this->addChild(clock, 998);

}

void GamePlayScene::LoseGame()
{
	this->unscheduleUpdate();
	PopupLoseGame *popupLose = PopupLoseGame::create();
	this->addChild(popupLose, 999);
	popupLose->getLayer()->setVisible(true);
	Constants::SetEnableAllTouchEventOnMapLevel(false);

	InfoMap::setScore(0);
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
		auto _rand = cocos2d::random(1, 2);
		if (objectA >= 100)
		{
			_result = ship->Collision(sharkList, objectB, objectA);
			if (!_result)
			{
				//DoClone(SharkAlive(objectB));
				if (_rand == 1)
				{
					SharkAlive(objectB)->Angry();
				}
				else
				{
					SharkAlive(objectB)->RunAwayAnimation();

				}
			}
		}
		else
		{
			_result = ship->Collision(sharkList, objectA, objectB);
			if (!_result)
			{
				//DoClone(SharkAlive(objectA));
				if (_rand == 2)
				{
					SharkAlive(objectA)->Angry();
				}
				else
				{
					SharkAlive(objectA)->RunAwayAnimation();
				}

			}
		}
	}
	//CCLOG("game play : colision");
	return false;
}

void GamePlayScene::initLevelEndGame()
{
	for (int i = 0; i < 16; i++)
	{
		MapLevel *level = new MapLevel();
		level->SetLevel(i);
		level->SetStar(0);
		mListLevelEnd.push_back(level);
	}
}

void GamePlayScene::setCountItem()
{
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT_LEVEL;
	labelConfig.fontSize = 25;
	//labelConfig.glyphs = GlyphCollection::DYNAMIC;
	//labelConfig.outlineSize = 1;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	/// boom is brick
	mLabelCountBrick = Label::createWithTTF(labelConfig, std::to_string(Constants::GetBricks()));
	mLabelCountBrick->setAlignment(TextHAlignment::CENTER);
	mLabelCountBrick->setColor(Color3B::BLACK);
	mLabelCountBrick->setPosition(cocos2d::Vec2(visibleSize.width*0.0905, visibleSize.height*0.061));
	this->addChild(mLabelCountBrick, 999);

	mCountHP = Label::createWithTTF(labelConfig, std::to_string(Constants::GetHps()));
	mCountHP->setAlignment(TextHAlignment::CENTER);
	mCountHP->setColor(Color3B::BLACK);
	mCountHP->setPosition(cocos2d::Vec2(visibleSize.width*0.198, visibleSize.height*0.061));
	this->addChild(mCountHP, 999);

	mCountGunE = Label::createWithTTF(labelConfig, std::to_string(Constants::GetBooms()));
	mCountGunE->setAlignment(TextHAlignment::CENTER);
	mCountGunE->setColor(Color3B::BLACK);
	mCountGunE->setPosition(cocos2d::Vec2(visibleSize.width*0.306, visibleSize.height*0.061));
	this->addChild(mCountGunE, 999);

}
