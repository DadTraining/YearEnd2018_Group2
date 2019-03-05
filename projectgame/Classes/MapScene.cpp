#include"Model.h"
#include"MapScene.h"
#include"define.h"
#include "Constants.h"
#include "InfoMap.h"
#include "PopUpShop.h"

Scene* MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//Constants::getVisibleSize() = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create(IMG_MAPSCENE);

	background->setPosition(Vec2(Constants::getVisibleSize().width / 2 + origin.x,
		Constants::getVisibleSize().height / 2 + origin.y));
	
	addChild(background, -1);

	initLevel();
	initPopUpLevel();

	setListButton();
	coin();
	star();
	shoppe();
	
	for (int i = 0; i < Constants::GetListMap().size(); i++)
	{
		auto map = Constants::GetListMap().at(i)->isAllowPlay();
		Constants::SetEnableTouchEvent(i, map);
	}

	Constants::setInMap(true);

	return true;
}

void MapScene::setListButton()
{
	//std::string png = ".png", normal, pressed, num = ".1", path = "map/";
	//char c[20] = {0}; //get number of picture

	char normal[20] = { 0 };
	char pressed[20] = { 0 };

	
	
	for (int i = 1; i < LIST_BUTTON_MAX + 1; i++)
	{
		////////////////
		//add button to list
		sprintf(normal, "map/%d.png", i);
		sprintf(pressed, "map/%d.1.png", i);
		
		auto button = ui::Button::create(normal,pressed,pressed);

		mListButton.push_back(button);

		///////////////////
		//set position for button
		switch (i)
		{
		case 1:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 6.31,
				Constants::getVisibleSize().height * 3.07 / 4));
			break;
		}
		case 2:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 4.1,
				Constants::getVisibleSize().height / 1.52));
			break;
		}
		case 3:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 4.65,
				Constants::getVisibleSize().height / 2.02));
			break;
		}
		case 4:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 7.55,
				Constants::getVisibleSize().height / 2.6));
			break;
		}
		case 5:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 5.46,
				Constants::getVisibleSize().height / 4.15));
			break;
		}
		case 6:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 3.37,
				Constants::getVisibleSize().height / 4.2));
			break;
		}
		case 7:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 2.65,
				Constants::getVisibleSize().height / 2.695));
			break;
		}
		case 8:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 2.61,
				Constants::getVisibleSize().height / 1.83));
			break;
		}
		case 9:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 2.1,
				Constants::getVisibleSize().height / 1.4));
			break;
		}
		case 10:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.7,
				Constants::getVisibleSize().height / 1.55));
			break;
		}
		case 11:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.65,
				Constants::getVisibleSize().height / 2.15));
			break;
		}
		case 12:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.87,
				Constants::getVisibleSize().height / 3.2));
			break;
		}
		case 13:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.49,
				Constants::getVisibleSize().height / 4.1));
			break;
		}
		case 14:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.31,
				Constants::getVisibleSize().height / 2.45));
			break;
		}
		case 15:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.23,
				Constants::getVisibleSize().height / 1.65));
			break;
		}
		case 16:
		{
			button->setPosition(Vec2(Constants::getVisibleSize().width / 1.4125,
				Constants::getVisibleSize().height / 1.3));
			break;
		}
		default:
			break;
		}

		this->addChild(button);			

		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				mListPlay[i - 1]->getLayer()->setVisible(true);
				Constants::SetPhase(i - 1);
				Constants::SetEnableAllTouchEventOnMapLevel(false);
				break;
			}
		});
		Constants::AddButtonIntoMapLevel(button);
	}
}

/*Init level*/
void MapScene::initLevel()
{
	for (int i = 0; i < 16; i++)
	{
		MapLevel *level = new MapLevel();
		level->SetLevel(i + 1);
		level->SetStar(0);
		mListLevel.push_back(level);
	}
}

/*Init Popup level*/
void MapScene::initPopUpLevel()
{
	/////////////////
	//creat popup play
	

	for (int i = 0; i < 16; i++)
	{
		PopupPlay *popup = PopupPlay::create();
		this->addChild(popup, 3);

		popup->getLayer()->setVisible(false);

		
		popup->setLevel(mListLevel[i]->GetLevel(), mListLevel[i]->GetStar());
		mListPlay.push_back(popup);
	}

}

void MapScene::setEnableTouch(bool enable)
{
	for (int i = 0; i < btnLevels.size(); i++)
	{
		btnLevels[i]->setTouchEnabled(enable);
	}
}

void MapScene::coin()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//frames coin
	auto mFramesCoin = cocos2d::Sprite::create(BUTTON_FRAMES);
	mFramesCoin->setPosition(cocos2d::Vec2(visibleSize.width / 11, visibleSize.height / 1.05));
	this->addChild(mFramesCoin);


	//icon coin
    mCoin =cocos2d:: Sprite::create(COIN);
	mCoin->setAnchorPoint(Vec2(0, 1));
	mCoin->setPosition(cocos2d::Vec2(visibleSize.width / 45, visibleSize.height / 1.015));
	this->addChild(mCoin);
	//lable coin
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT_SCORE;
	labelConfig.fontSize = 31;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 2;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	mcoin = Constants::GetTotalCoin();
	//mcoin = 11111;
	auto mLableCoin=Label::createWithTTF(labelConfig, std::to_string(mcoin));
	mLableCoin->setAnchorPoint(Vec2(0, 1));
	mLableCoin->setPosition(cocos2d::Vec2(visibleSize.width / 15, visibleSize.height / 1.03));
	mLableCoin->enableGlow(Color4B::BLUE);
	this->addChild(mLableCoin);


}

void MapScene::star()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//frames
	auto mFramesStar = cocos2d::Sprite::create(BUTTON_FRAMES_STAR);
	mFramesStar->setPosition(cocos2d::Vec2(visibleSize.width / 4.2, visibleSize.height / 1.05));
	this->addChild(mFramesStar);
	//icon star
    mStar = cocos2d::Sprite::create(STAR);
	mStar->setAnchorPoint(Vec2(0, 1));
	mStar->setPosition(cocos2d::Vec2(visibleSize.width / 5.3, visibleSize.height / 1.01));
	mStar->setScale(0.5);
	this->addChild(mStar);

	// lable star
	TTFConfig labelConfig;
	labelConfig.fontFilePath = FONT_SCORE;
	labelConfig.fontSize = 31;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 2;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	mstar = Constants::GetTotalStar();
	//mstar = 111;
	auto mLableStar = Label::createWithTTF(labelConfig, std::to_string(mstar));
	mLableStar->setAnchorPoint(Vec2(0, 1));
	mLableStar->setPosition(cocos2d::Vec2(visibleSize.width / 4.2, visibleSize.height / 1.03));
	mLableStar->enableGlow(Color4B::BLUE);
	this->addChild(mLableStar);

}

void MapScene::shoppe()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//button shop
	auto btnShop = ui::Button::create(SHOP);
	btnShop->setPosition(cocos2d::Vec2(visibleSize.width / 1.05 , visibleSize.height / 1.05));
	
	btnShop->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:	
			//PopUpShop*popupshop = PopUpShop::create();
			//this->addChild(popupshop);
			PopUpShop* popupshop = PopUpShop::create();
			this->addChild(popupshop);
			break;
		}
	});
	this->addChild(btnShop);
}
