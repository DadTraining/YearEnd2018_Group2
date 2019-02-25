#include "MapLevel.h"
#include "define.h"

MapLevel::MapLevel()
{
}

MapLevel::MapLevel(cocos2d::Scene * scene, int lv, int st)
{

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
