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
#include "PopUpPlay.h"
#include "PopUpSetting.h"
#include "define.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

bool PopupPlay::init()
{
	Popup::init();
	Popup::setBackground();

	///////////////
	//Button play
	auto btnPlay = ui::Button::create(BUTTON_PLAY);
	btnPlay->setPosition(Vec2(0, -mBackground->getContentSize().height / 4
								+ mBackground->getContentSize().height / 22));
	
	mLayer->addChild(btnPlay, 1);
	btnPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});

	////////////////
	//Button setting
	auto btnSetting = ui::Button::create(BUTTON_SETTING);
	btnSetting->setPosition(Vec2(- mBackground->getContentSize().width / 7, 
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnSetting->setScale(0.75);
	mLayer->addChild(btnSetting, 1);
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			PopupSetting *popup = PopupSetting::create();
			this->addChild(popup, 3);
			break;
		}
	});
	return true;
}

void PopupPlay::onExit()
{
	Popup::onExit();
}

/*Set level popup*/
void PopupPlay::setLevel(int numLevel, int numStars)
{
	std::string png = ".png", stars = "stars", path = "map/", l = "level", le, st;
	char cLevel = '0' + numLevel;
	le = path + l + cLevel + png; //path of level png
	
	auto lv = Sprite::create(le);
	lv->setPosition(Vec2(0, mBackground->getContentSize().height / 5));
	mLayer->addChild(lv);

	char cStars = '0' + numStars;
	st = path + cStars + stars + png;
	auto star = Sprite::create(st);
	star->setPosition(Vec2(0, mBackground->getContentSize().height / 17));
	star->setScale(0.5);
	mLayer->addChild(star);
}
