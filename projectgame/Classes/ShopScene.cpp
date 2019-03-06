#include"Model.h"
#include"ShopScene.h"
#include"define.h"
#include "Constants.h"
#include "InfoMap.h"
#include "PopUpShop.h"
#include "MapScene.h"


Scene* ShopScene::createScene()
{
	return ShopScene::create();
}

bool ShopScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create(WATER);

	background->setPosition(Vec2(Constants::getVisibleSize().width / 2 + origin.x,
		Constants::getVisibleSize().height / 2 + origin.y));

	addChild(background, -1);

	mShop = Sprite::create(SHOP_BG);

	mShop->setPosition(Vec2(Constants::getVisibleSize().width / 2 + origin.x,
		Constants::getVisibleSize().height / 2 + origin.y));

	addChild(mShop);
	coin();
	buyFrame();
	comeback();


	return true;
}



void ShopScene::coin()
{
	//icon coin
	auto mCoin = cocos2d::Sprite::create(COIN);
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
	mLableCoin = Label::createWithTTF(labelConfig, std::to_string(mcoin));
	mLableCoin->setAnchorPoint(Vec2(0, 1));
	mLableCoin->setPosition(cocos2d::Vec2(visibleSize.width / 15, visibleSize.height / 1.03));
	mLableCoin->enableGlow(Color4B::BLUE);
	
	this->addChild(mLableCoin);
}

void ShopScene::buyFrame()
{
	//frames
	auto buyItem1 = cocos2d::ui::Button::create(BUTTON_BUY);
	buyItem1->setPosition(cocos2d::Vec2(mShop->getPosition().x - mShop->getContentSize().width / 3,
		mShop->getPosition().y));
	this->addChild(buyItem1, 1);

	auto buyItem2 = cocos2d::ui::Button::create(BUTTON_BUY);
	buyItem2->setPosition(cocos2d::Vec2(mShop->getPosition().x + 2,
		mShop->getPosition().y));
	this->addChild(buyItem2, 1);

	auto buyItem3 = cocos2d::ui::Button::create(BUTTON_BUY);
	buyItem3->setPosition(cocos2d::Vec2(mShop->getPosition().x + mShop->getContentSize().width / 3 + 5,
		mShop->getPosition().y));
	this->addChild(buyItem3, 1);

	auto costItem1 = Label::createWithTTF(std::to_string(COST_BUY_BRICK), FONT_SCORE, 31);
	costItem1->setAnchorPoint(Vec2(0, 0.5));
	costItem1->setPosition(buyItem1->getPosition());
	costItem1->enableGlow(Color4B::BLUE);
	this->addChild(costItem1, 2);

	auto costItem2 = Label::createWithTTF(std::to_string(COST_BUY_HP), FONT_SCORE, 31);
	costItem2->setAnchorPoint(Vec2(0, 0.5));
	costItem2->setPosition(buyItem2->getPosition());
	costItem2->enableGlow(Color4B::BLUE);
	this->addChild(costItem2, 2);

	auto costItem3 = Label::createWithTTF(std::to_string(COST_BUY_BOOM), FONT_SCORE, 31);
	costItem3->setAnchorPoint(Vec2(0, 0.5));
	costItem3->setPosition(buyItem3->getPosition());
	costItem3->enableGlow(Color4B::BLUE);
	this->addChild(costItem3, 2);

	buyItem1->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:

			break;
		case ui::Widget::TouchEventType::ENDED:
			//cocos2d::Director::getInstance()->replaceScene(this);
			Constants::BuyBricks();
			mLableCoin->setString(std::to_string(Constants::GetTotalCoin()));
		
			break;
		}
	});

	buyItem2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;

		case ui::Widget::TouchEventType::ENDED:
			Constants::BuyHps();
			mLableCoin->setString(std::to_string(Constants::GetTotalCoin()));

			break;
		}
	});

	buyItem3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;

		case ui::Widget::TouchEventType::ENDED:
			Constants::BuyBooms();
			mLableCoin->setString(std::to_string(Constants::GetTotalCoin()));

			break;
		}
	});
}

void ShopScene::comeback()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//button comeback
	auto btnComeback = ui::Button::create(BUTTON_COMEBACK);
	btnComeback->setPosition(cocos2d::Vec2(visibleSize.width / 1.05, visibleSize.height / 1.05));
	this->addChild(btnComeback);
	btnComeback->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, MapScene::createScene()));
			break;
		}
	});


}
