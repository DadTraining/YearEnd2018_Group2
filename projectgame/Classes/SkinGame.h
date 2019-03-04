#pragma once
#include "cocos2d.h"
using namespace std;
class SkinGame
{
private:
	int mID;
	string mSkinText;
	bool mAllowUse;
	bool mIssue;

public:
	SkinGame(int id, string skintext, bool allowuse, bool issue);
	SkinGame();
	int GetID();
	void SetID(int id);
	string GetSkinText();
	void SetSkinText(string text);
	bool IsAllowUse();
	void SetAllowUse(bool allow);
	bool IsIssue();
	void SetIssue(bool issue);


};

