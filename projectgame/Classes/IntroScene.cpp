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

#include "IntroScene.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
    return IntroScene::create();
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Page();
    return true;
}

void IntroScene::Page()
{
	auto pageView = ui::PageView::create();
	pageView->setContentSize(Size(SCREEN_W, SCREEN_H));
	pageView->setBounceEnabled(true);
	pageView->setAnchorPoint(Vec2(0.5, 0.5));
	pageView->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2));
	this->addChild(pageView);

	for (int i = 0; i < 3; i++)
	{
		auto layout = ui::Layout::create();
		layout->setContentSize(pageView->getContentSize());
		auto sprite = Sprite::create("HelloWorld.png");
		sprite->setPosition(layout->getSize().width / 2, layout->getSize().height / 2);
		layout->addChild(sprite);
		pageView->addPage(layout);

	}
	pageView->scrollToItem(3);
}

