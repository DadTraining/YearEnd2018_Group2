#include "MapLevel.h"
#include "define.h"

MapLevel::MapLevel(int lv, int star, int p1, int p2, int p3, int sharkSkin, bool PlayPass, int score, bool allow)
{
	this->mLevel = lv;
	this->mStar = star;
	this->sharksPharse1 = p1;
	this->sharksPharse2 = p2;
	this->sharksPharse3 = p3;
	this->sharksSkin = sharkSkin;
	this->wasPlayPass = PlayPass;
	this->mScore = score;
	this->mAllowPlay = allow;
}

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

int MapLevel::GetPhase(int phase)
{
	switch (phase)
	{
		case 1:
			return sharksPharse1;
			break;
		case 2:
			return sharksPharse2;
			break;
		case 3:
			return sharksPharse3;
			break;
		default:
			return 0;
			break;
	}
}

void MapLevel::setPlayPass(bool pas)
{
	wasPlayPass = pas;
}

void MapLevel::AllowPlay()
{
	mAllowPlay = true;
}

