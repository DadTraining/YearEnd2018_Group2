#pragma once

#include "cocos2d.h"
class Popup : public cocos2d::Node
{
protected:
	cocos2d::Layer *mLayer;
	cocos2d::Sprite *mBackground;
public:

	virtual bool init();
	virtual void onExit();
	void setBackground();
	void disappear();
	
	cocos2d::Layer* getLayer();

	/*
		this function handle event touch exit button. can override in its children
	*/
	virtual void HandlTouch();
	CREATE_FUNC(Popup);

};
