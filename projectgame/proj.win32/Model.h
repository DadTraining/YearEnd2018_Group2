#pragma once
#include "cocos2d.h"
#include"ui\CocosGUI.h"
using namespace cocos2d;
class Model
{
protected:
	cocos2d::Sprite* mSprite;
	cocos2d::Vec2 mPos;
	bool mVisible;
public:
	Model();
	virtual ~Model();

	cocos2d::Vec2 GetPosition();
	void SetPosition(cocos2d::Vec2 mPos);

	cocos2d::Sprite* GetSprite();
	void SetSprite(cocos2d::Sprite* sprite);

	void SetVisible(bool vis);
	bool IsVisible();

	virtual void Update() = 0;
	virtual void Init() = 0;
	cocos2d::Vec2 GetLocation();
};

