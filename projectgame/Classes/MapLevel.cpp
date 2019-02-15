#include "MapLevel.h"
#include "define.h"

MapLevel::MapLevel()
{
}

MapLevel::MapLevel(cocos2d::Scene * scene, int lv, int st)
{
	//auto Layer = cocos2d::Layer::create();
	//auto bt2 =cocos2d::Sprite::create(DIALOG_MAP);
	//bt2->setScale(0.2);
	////bt2->setPosition(Vec2(SCREEN_W/2, SCREEN_H/2));
	//bt2->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//scene->addChild(bt2, 100);
	//auto Lable2 = cocos2d::Sprite::create(Lable_2);
	//Lable2->setScale(0.5);
	//Lable2->setPosition(cocos2d::Vec2(SCREEN_W / 2, SCREEN_H / 1.55));
	//addChild(Lable2);
	//auto IMG_Star = cocos2d::Sprite::create(IMG_STAR);
	//IMG_Star->setScale(0.5);
	//IMG_Star->setPosition(cocos2d::Vec2(SCREEN_W / 2, SCREEN_H / 1.85));
	//addChild(IMG_Star);
}

MapLevel::~MapLevel()
{
}

int MapLevel::GetLevel()
{
	return mLevel;
}

void MapLevel::SetLevel(int lv)
{
	mLevel = lv;
}

int MapLevel::GetStar()
{
	return mStar;
}

void MapLevel::SetStar(int st)
{
	mStar = st;
}

bool MapLevel::OnBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return false;
}
