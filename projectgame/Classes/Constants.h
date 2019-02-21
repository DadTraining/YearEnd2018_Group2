#pragma once
#include "cocos2d.h"


class Constants 
{
private:
	//static cocos2d::Size mSize;
public:
	static cocos2d::Size getVisibleSize();
	static float setScaleSprite(float whichSize,float expectSize, float realSize);

};

