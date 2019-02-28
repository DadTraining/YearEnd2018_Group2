#pragma once
#include "cocos2d.h"
#include"ui\CocosGUI.h"
//using namespace cocos2d;
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

	void SetSprite(cocos2d::Sprite* sprite);

	virtual void Update() = 0;
	virtual void Init() = 0;
	cocos2d::Vec2 GetLocation();
	void SetPosition(cocos2d::Vec2 mPos);
	void SetVisible(bool vis);
	bool IsVisible();
	void SetAlive(bool vis);
	void SetSpriteVisible(bool vis);
	bool SpriteIsVisible();
	cocos2d::Animation* CreateAnimation(std::string name, int start, int frames, float delay);

	virtual cocos2d::Rect GetRect();
	void SetTag(int tag);

	bool IsAlive();
	cocos2d::Sprite* GetSprite();
	cocos2d::Vec2 GetPosition();




};
