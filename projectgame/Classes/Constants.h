#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MapLevel.h"
#include <vector>
#include "InfoMap.h"


class Constants 
{
private:
	//static cocos2d::Size mSize;
	static cocos2d::Vector<cocos2d::ui::Button*> listButton;
	static std::vector<MapLevel*> listMap;

public:
	static cocos2d::Size getVisibleSize();
	static float setScaleSprite(float whichSize,float expectSize, float realSize);

	static void AddButtonIntoMapLevel(cocos2d::ui::Button* btn);
	static void SetEnableTouchEvent(int index,bool enable);
	static void SetEnableAllTouchEventOnMapLevel(bool enable);

	static  std::vector<MapLevel*> GetListMap();
	static void AddMapIntoList(MapLevel* map);

	static void SetPhase(int index);
	static void ReleaseButton();
};

