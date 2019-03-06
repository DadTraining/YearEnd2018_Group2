/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopupPause.h"
#include "PopUpSetting.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include "MapScene.h"

USING_NS_CC;

bool PopupPause::init()
{
	Popup::init();
	Popup::setBackground();
	auto title = Sprite::create("button/pause_bg.png");
	title->setPosition(Vec2(0, mBackground->getContentSize().height / 7));
	mLayer->setPosition(Constants::getVisibleSize().width/2, Constants::getVisibleSize().height / 1.7);
	mLayer->addChild(title);
	title->setScale(0.75);

	///////////////
	//Button play
	auto btnPlay = ui::Button::create(BUTTON_REPLAY_IMG);
	btnPlay->setPosition(Vec2(0, -mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	mLayer->addChild(btnPlay, 1);
	btnPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->resume();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});

	////////////////
	//Button home
	auto btnHome = ui::Button::create(BUTTON_HOME);
	btnHome->setPosition(Vec2(-mBackground->getContentSize().width / 7,
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnHome->setScale(0.75);
	mLayer->addChild(btnHome, 1);
	btnHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->resume();
			Constants::ReleaseButton();
			Director::getInstance()->replaceScene(MapScene::createScene());
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			break;

		}
	});
	return true;
}
void PopupPause::onExit()
{
	Popup::onExit();
}

void PopupPause::HandlTouch()
{
	Constants::SetEnableAllTouchEventOnMapLevel(true);
	mLayer->setVisible(false);
	cocos2d::Director::getInstance()->resume();
}


