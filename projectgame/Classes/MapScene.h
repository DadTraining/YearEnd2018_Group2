#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "PopUpPlay.h"
#include "Popup.h"
#include "ui\CocosGUI.h"

using namespace cocos2d;
using namespace std;

class MapScene :public cocos2d::Scene
{
private:
	std::vector<cocos2d::ui::Button*> mListButton;
	std::vector<MapLevel*> mListLevel;
	std::vector<PopupPlay*> mListPlay;
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	void setListButton();
	void initLevel();
	void initPopUpLevel();
	void setEnableTouch(bool enable);
	CREATE_FUNC(MapScene);
};