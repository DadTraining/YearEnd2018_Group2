#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PopUpPlay.h"
#include "Popup.h"
#include "ui\CocosGUI.h"
#include "GamePlayScene.h"

using namespace cocos2d;
using namespace std;

class MapScene :public cocos2d::Scene
{
private:
	std::vector<cocos2d::ui::Button*> mListButton;
	std::vector<MapLevel*> mListLevel;
	std::vector<PopupPlay*> mListPlay;
	std::vector<ui::Button*> btnLevels;
	cocos2d::Sprite* mCoin;
	cocos2d::Sprite* mStar;
	int mcoin;
	int mstar;
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	void setListButton();
	void initLevel();
	void initPopUpLevel();
	void setEnableTouch(bool enable);
	void coin();
	void star();
	void shoppe();
	CREATE_FUNC(MapScene);
	
};