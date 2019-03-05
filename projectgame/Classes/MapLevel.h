#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
class MapLevel
{
protected:
	int mLevel;
	int mStar;
	int sharksPharse1;
	int sharksPharse2;
	int sharksPharse3;
	int sharksSkin;
	int mScore;
	bool wasPlayPass;
	bool mAllowPlay;

	cocos2d::Vec2 mPos;

public:
	MapLevel(int lv, int star, int p1, int p2, int p3, int shaSkin,  int score, bool PlayPass, bool allow);
	MapLevel();
	MapLevel(cocos2d::Scene* scene,int lv, int st);
	virtual ~MapLevel();



	int GetLevel();
	void SetLevel(int lv);
	int GetStar();
	void SetStar(int st);

	int GetPhase(int phase);
	bool WasPlay() {
		return wasPlayPass;
	}

	bool isAllowPlay() {
		return mAllowPlay;
	}

	void SetScore(int score) {
		mScore = score;
	}
	void setPlayPass(bool pas);

	void AllowPlay();
	int GetSharksSkin();
	int GetScore();

	void SetPosition(cocos2d::Vec2 pos);
	void ShowStar(cocos2d::Scene* scene);
};
