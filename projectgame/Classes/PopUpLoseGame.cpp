#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopupLoseGame.h"
#include "PopUpSetting.h"
#include "MapScene.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include"InfoMap.h"
#include"Constants.h"

USING_NS_CC;

bool PopupLoseGame::init()
{
	Popup::init();
	Popup::setBackground();

	// Text you lose
	auto losegame = Sprite::create(LOSE_GAME);
	losegame->setPosition(SCREEN_W/2,SCREEN_H/2);
	this->addChild(losegame);
	
	//Button replay
	auto btnRePlay = ui::Button::create(BUTTON_MAP_REPLAY);
	btnRePlay->setPosition(Vec2(- mBackground->getContentSize().width / 7,
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnRePlay->setScale(0.75);
	mLayer->addChild(btnRePlay, 1);
	btnRePlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->resume();
			Constants::ReleaseButton();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});
	

	return true;
}

void PopupLoseGame::onExit()
{
	Popup::onExit();
}

void PopupLoseGame::HandlTouch()
{
	cocos2d::Director::getInstance()->resume();
	Constants::ReleaseButton();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1, MapScene::createScene()));
	mLayer->setVisible(false);
}

	


	
