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
#include "PopUpSetting.h"
#include "define.h"


USING_NS_CC;

bool PopupSetting::init()
{
	Popup::init();
	Popup::setBackground();

	///////////////
	//Add label setting
	auto setting = cocos2d::Sprite::create(SETTING);
	setting->setPosition(Vec2(0, mBackground->getContentSize().height / 7));
	mLayer->addChild(setting);
	setting->setScale(0.75);
	
	///////////////
	//Add label mBgm and mSfx
	mSfx = cocos2d::Sprite::create(SFX);
	mSfx->setPosition(Vec2(-mBackground->getContentSize().width / 6,
		setting->getPosition().y - mBackground->getContentSize().height / 8));
	mLayer->addChild(mSfx);
	mSfx->setScale(0.75);

	mBgm = cocos2d::Sprite::create(BGM);
	mBgm->setPosition(Vec2(mSfx->getPosition().x, 
		mSfx->getPosition().y - mBackground->getContentSize().height / 10));
	mLayer->addChild(mBgm);
	mBgm->setScale(0.75);

	////////////////
	//Add slider of mBgm and mSfx
	sliderBGM();
	sliderSFX();
	
	////////////////
	//Add button accept
	auto btnAccept = cocos2d::ui::Button::create(BUTTON_EXIT);
	btnAccept->setScale(0.75);
	btnAccept->setPosition(cocos2d::Vec2(-mBackground->getContentSize().width / 7,
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	mLayer->addChild(btnAccept);
	btnAccept->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType t) {
		switch (t)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;

		}
	});

	return true;
}

void PopupSetting::onExit()
{
	Popup::onExit();
}

/*Add Slider*/
void PopupSetting::sliderBGM()
{
	
	auto sliderB = cocos2d::ui::Slider::create();
	sliderB->loadBarTexture(SLIDE_BAR_BG);
	sliderB->loadSlidBallTextureNormal(SLIDE_ROUND);
	sliderB->loadProgressBarTexture(SLIDE_BAR_PROGRESS);
	sliderB->setAnchorPoint(Vec2(0, 0.5));
	sliderB->setScale(0.45);

	sliderB->setPosition(Vec2(mBgm->getPosition().x + mBackground->getContentSize().width / 12,
		mBgm->getPosition().y));
	mLayer->addChild(sliderB);

	sliderB->addEventListener([&](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider *_slider = dynamic_cast<ui::Slider*>(sender);
			mPercentBGM = _slider->getPercent();
			break;
		}
		default:
			break;
		}
	});
}

void PopupSetting::sliderSFX()
{

	auto sliderS = cocos2d::ui::Slider::create();
	sliderS->loadBarTexture(SLIDE_BAR_BG);
	sliderS->loadSlidBallTextureNormal(SLIDE_ROUND);
	sliderS->loadProgressBarTexture(SLIDE_BAR_PROGRESS);
	sliderS->setAnchorPoint(Vec2(0, 0.5));
	sliderS->setScale(0.45);

	sliderS->setPosition(Vec2(mSfx->getPosition().x + mBackground->getContentSize().width / 12,
		mSfx->getPosition().y));
	mLayer->addChild(sliderS);

	sliderS->addEventListener([&](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider *_slider = dynamic_cast<ui::Slider*>(sender);
			mPercentSFX = _slider->getPercent();
			break;
		}
		default:
			break;
		}
	});
}
