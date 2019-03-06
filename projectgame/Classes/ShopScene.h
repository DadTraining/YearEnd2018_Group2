#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PopUpPlay.h"
#include "Popup.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GamePlayScene.h"

using namespace cocos2d;
using namespace std;

class ShopScene :public cocos2d::Scene
{
private:
	cocos2d::Sprite* mStar;
	cocos2d::Sprite* mShop;
	int mcoin;
	int mstar;
	Size visibleSize;
	cocos2d::Label* mLableCoin;
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	

	void coin();
	void buyFrame();
	void comeback();
	CREATE_FUNC(ShopScene);
	
};