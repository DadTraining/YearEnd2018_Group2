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
#include "ui\CocosGUI.h"

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
	//Add label BGM and SFX
	auto sfx = cocos2d::Sprite::create(SFX);
	sfx->setPosition(Vec2(-mBackground->getContentSize().width / 6, 
		setting->getPosition().y - mBackground->getContentSize().height / 8));
	mLayer->addChild(sfx);
	sfx->setScale(0.75);

	auto bgm = cocos2d::Sprite::create(BGM);
	bgm->setPosition(Vec2(sfx->getPosition().x, 
		sfx->getPosition().y - mBackground->getContentSize().height / 10));
	mLayer->addChild(bgm);
	bgm->setScale(0.75);

	
	return true;
}

void PopupSetting::onExit()
{
	Popup::onExit();
}

/*Add Slider*/
void PopupSetting::slider()
{
	
	auto slider = ui::Slider::create();
	slider->loadBarTexture(SLIDE_BAR_BG);
	slider->loadSlidBallTextureNormal(SLIDE_ROUND);
	slider->loadProgressBarTexture(SLIDE_BAR_PROGRESS);
	slider->setAnchorPoint(Vec2(0, 0.5));
	slider->setScale(0.5);

	slider->setPosition(Vec2(bgm->getPosition().x + mBackground->getContentSize().width / 10,
		bgm->getPosition().y));
	mLayer->addChild(slider);


}

/*Slider Event*/
void PopupSetting::slilderEvent(Ref * sender, ui::Slider::EventType type)
{
	switch (type)
	{
	case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		ui::Slider *_slider = dynamic_cast<ui::Slider*>(sender);
		int percentage = _slider->getPercent();

		break;
	}
	default:
		break;
	}
}
