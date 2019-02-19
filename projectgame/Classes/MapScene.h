#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"ui\CocosGUI.h"

using namespace cocos2d;
using namespace std;

class MapScene :public cocos2d::Scene
{
private:
	std::vector<cocos2d::ui::Button*> listButton;

public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	void setListButton();
	CREATE_FUNC(MapScene);
};