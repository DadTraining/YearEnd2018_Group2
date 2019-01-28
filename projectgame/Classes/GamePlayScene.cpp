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
#include "Shark.h"
#include <vector>
#include "define.h"	
USING_NS_CC;


#pragma region Shark
std::vector<Shark*> sharkList;
int callBackAlive;
Shark* sk;
#pragma endregion


Scene* GamePlayScene::createScene()
{
	return GamePlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shark/sprites.plist", "shark/sprites.png");

	for (int i = 0; i < SHARK_MAX_ON_SCREEN; i++)
	{
		sharkList.push_back(new Shark(this));
	}
	//sk = new Shark(this);
	//sk->SetVisible(true);
	callBackAlive = 0;
	this->scheduleUpdate();
	return true;
}


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
}

void GamePlayScene::update(float delta)
{
//	sk->Update();
	callBackAlive += 1;
	if (callBackAlive % SHARK_CALL_BACK_ALIVE == 0)
	{
		GamePlayScene::SharkAliveCallBack();
	}

	for (int i = 0; i < sharkList.size(); i++)
	{
		if (sharkList[i]->IsVisible())
		{
			sharkList[i]->Update();
		}
	}
}

void GamePlayScene::SharkAliveCallBack()
{
	for (int i = 0; i < sharkList.size(); i++)
	{
		if (!sharkList[i]->IsVisible())
		{
			//sharkList[i]->SetVisible(true);
			sharkList[i]->Init();
			break;
		}
	}
}
