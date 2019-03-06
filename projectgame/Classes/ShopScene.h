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
	cocos2d::Sprite* mCoin;
	cocos2d::Sprite* mStar;
	int mcoin;
	int mstar;
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	

	void coin();
	void star();
	void comeback();
	CREATE_FUNC(ShopScene);
	
};