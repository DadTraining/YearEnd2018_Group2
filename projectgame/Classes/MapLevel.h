#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
class MapLevel
{
protected:
	int mLevel;
	int mStar;
	
public:
	MapLevel();
	MapLevel(cocos2d::Scene* scene,int lv, int st);
	virtual ~MapLevel();



	int GetLevel();
	void SetLevel(int lv);
	int GetStar();
	void SetStar(int st);

	bool OnBegan(cocos2d::Touch* touch, cocos2d::Event * event);
};
