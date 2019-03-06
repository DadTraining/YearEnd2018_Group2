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

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create();

	background->setPosition(Vec2(Constants::getVisibleSize().width / 2 + origin.x,
		Constants::getVisibleSize().height / 2 + origin.y));
	
	addChild(background, -1);
	coin();
	star();
	comeback();
	
	
	return true;
}



void ShopScene::coin()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//frames coin
	auto mFramesCoin = cocos2d::Sprite::create(BUTTON_FRAMES);
	mFramesCoin->setPosition(cocos2d::Vec2(visibleSize.width / 11, visibleSize.height / 1.05));
	this->addChild(mFramesCoin);


	//icon coin
	mCoin = cocos2d::Sprite::create(COIN);
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
	auto mLableCoin = Label::createWithTTF(labelConfig, std::to_string(mcoin));
	mLableCoin->setAnchorPoint(Vec2(0, 1));
	mLableCoin->setPosition(cocos2d::Vec2(visibleSize.width / 15, visibleSize.height / 1.03));
	mLableCoin->enableGlow(Color4B::BLUE);
	this->addChild(mLableCoin);


}

void ShopScene::star()
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

void ShopScene::comeback()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//button comeback
	auto btnComeback = ui::Button::create(BUTTON_COMEBACK);
	btnComeback->setPosition(cocos2d::Vec2(visibleSize.width / 1.05 , visibleSize.height / 1.05));
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
