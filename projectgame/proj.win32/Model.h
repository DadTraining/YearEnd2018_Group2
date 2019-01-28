#pragma once
#include "cocos2d.h"
class Model
{
protected:
	cocos2d::Sprite* mSprite;
	cocos2d::Vec2 mPos;
	bool mVisible;
public:
	Model();
 	virtual ~Model();

	void SetVisible(bool vis);
	bool IsVisible();

	virtual void Update() = 0;
	virtual void Init() = 0;
};

