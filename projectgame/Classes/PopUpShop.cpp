#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopUpShop.h"
#include "PopUpSetting.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include"Model.h"
#include"MapScene.h"




//PopUpShop::PopUpShop(cocos2d::Scene * createScene)
//{
//	// layer 
//	mLayer = cocos2d::Layer::create();
//	mLayer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
//	mLayer->setPosition(SCREEN_W /200, SCREEN_H / 200);
//	createScene->addChild(mLayer);
//}

bool PopUpShop::init()
{
	if (!Node::init()) return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	mLayer = cocos2d::Layer::create();
	//mLayer->setAnchorPoint(cocos2d::Vec2(0, 0));
	mLayer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mLayer);

	
	setBackground();
	return true;
}

void PopUpShop::onExit()
{
	Node::onExit();
}

void PopUpShop::setBackground()
{
	// backgroud
	mBackground = Sprite::create(BACKGROUNDSHOP);
	mBackground->setPosition(cocos2d::Vec2::ZERO);
	mLayer->addChild(mBackground, -1);

	//button exit
	auto btnExitShop = cocos2d::ui::Button::create(BUTTON_EXIT);
	btnExitShop->setPosition(cocos2d::Vec2(mBackground->getContentSize().width / 2 - 20,
		mBackground->getContentSize().height / 2 - 30));
	btnExitShop->setScale(0.5);
	btnExitShop->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:

			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			HandlTouch();
			break;

		}
	});
	mLayer->addChild(btnExitShop);
}

void PopUpShop::disappear()
{

}

cocos2d::Layer * PopUpShop::getLayer()
{
	return mLayer;
}

void PopUpShop::HandlTouch()
{
	mLayer->setVisible(false);
	cocos2d::Director::getInstance()->resume();
}





