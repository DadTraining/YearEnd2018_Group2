#include "MapLevel.h"
#include "define.h"

MapLevel::MapLevel(int lv, int star, int p1, int p2, int p3, int sharkSkin, int score, bool PlayPass, bool allow, int star3, int star2)
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
	this->score2 = star2;
	this->score3 = star3;
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

int MapLevel::GetSharksSkin()
{
	return sharksSkin;
}

int MapLevel::GetScore()
{
	return mScore;
}


void MapLevel::SetPosition(cocos2d::Vec2 pos)
{
	mPos = pos;
}

void MapLevel::ShowStar(cocos2d::Scene * scene)
{
	std::string _name;
	switch (mStar)
	{
	case 0:
		_name = MAPSCENE_ZERO_STAR;
		break;
	case 1:
		_name = MAPSCENE_ONE_STAR;

		break;
	case 2:
		_name = MAPSCENE_TWO_STAR;

		break;
	case 3:
		_name = MAPSCENE_THREE_STAR;

		break;
	}

	auto sprite = cocos2d::Sprite::create(_name);
	sprite->setPosition(mPos);
	scene->addChild(sprite);
}

