#include "Popup.h"
#include "define.h"
#include"ui\CocosGUI.h"

bool Popup::init()
{
	//if (!Node::init()) return false;

	//mLayer = cocos2d::Layer::create();
	//mLayer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	//mLayer->setPosition(SCREEN_W / 2, SCREEN_H / 2);
	//addChild(mLayer);

	//auto background = cocos2d::Sprite::create(DIALOG_MAP);
	//background->setPosition(0, 0);

	//
	////background->setScaleX(POPUP_SCALE_X);
	////background->setScaleY(POPUP_SCALE_Y);
	//mLayer->addChild(background, -1);
	return true;
}

void Popup::onExit()
{
	/*Node::onExit();*/
}

void Popup::setBackground()
{
	mLayer = cocos2d::Layer::create();
	mLayer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	mLayer->setPosition(SCREEN_W / 2, SCREEN_H / 2);
	addChild(mLayer);

	mBackground = cocos2d::Sprite::create(DIALOG_MAP);
	mBackground->setPosition(0, 0);

	
	mBackground->setScaleX(POPUP_SCALE_X);
	mBackground->setScaleY(POPUP_SCALE_Y);
	mLayer->addChild(mBackground, -1);
}
