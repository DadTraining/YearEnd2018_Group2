#include "Popup.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include "Constants.h"

bool Popup::init()
{
	if (!Node::init()) return false;

	mLayer = cocos2d::Layer::create();
	mLayer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	mLayer->setPosition(SCREEN_W / 2, SCREEN_H / 2);
	addChild(mLayer);
	return true;
}

void Popup::onExit()
{
	Node::onExit();
}

void Popup::setBackground()
{
	mBackground = cocos2d::Sprite::create(DIALOG_MAP);
	mBackground->setPosition(0, 0);


	mBackground->setScaleX(POPUP_SCALE_X);
	mBackground->setScaleY(POPUP_SCALE_Y);
	mLayer->addChild(mBackground, -1);

	auto btnExit = cocos2d::ui::Button::create(BUTTON_EXIT);
	btnExit->setScale(0.75);
	btnExit->setPosition(cocos2d::Vec2(mBackground->getContentSize().width / 7, -mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	mLayer->addChild(btnExit);
	btnExit->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType t) {
		switch (t)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			//disappear();
			mLayer->setVisible(false);
			Constants::SetEnableTouchEvent(true);
			//mLayer->removeFromParentAndCleanup(true);
			break; 
	
		}
	});

}

void Popup::disappear()
{
	auto dis = cocos2d::TargetedAction::create(mLayer, cocos2d::FadeOut::create(3));
	this->runAction(dis);

}

cocos2d::Layer* Popup::getLayer()
{
	return mLayer;
}

