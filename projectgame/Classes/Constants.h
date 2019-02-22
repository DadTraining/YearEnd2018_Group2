#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class Constants 
{
private:
	//static cocos2d::Size mSize;
	static cocos2d::Vector<cocos2d::ui::Button*> listButton;
public:
	static cocos2d::Size getVisibleSize();
	static float setScaleSprite(float whichSize,float expectSize, float realSize);

	static void AddButtonIntoMapLevel(cocos2d::ui::Button* btn);
	static void SetEnableTouchEvent(bool enable);
};

