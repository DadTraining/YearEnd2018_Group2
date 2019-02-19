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

#pragma once
#include "cocos2d.h"
#include"Bullet.h"
#include"Ship.h"

class GamePlayScene : public cocos2d::Scene
{
private:
	Ship * ship;
	Vec2 mLocation;
	cocos2d::PhysicsWorld* mPhysicsWorld;
public:
	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init() override;

	void update(float delta) override;
	// implement the "static create()" method manually
	void SharkAliveCallBack();

	bool onTouchBegan(Touch *touch, Event *event);
	bool onContactBegin(PhysicsContact& contact);

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { mPhysicsWorld = world; }

	CREATE_FUNC(GamePlayScene);
};

