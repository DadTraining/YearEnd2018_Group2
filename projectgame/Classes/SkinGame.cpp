#include "SkinGame.h"

SkinGame::SkinGame(int id, string skintext, bool allowuse, bool issue)
{
	this->mID = id;
	this->mSkinText = skintext;
	this->mAllowUse = allowuse;
	this->mIssue = issue;
}

SkinGame::SkinGame()
{
}

int SkinGame::GetID()
{
	return mID;
}

void SkinGame::SetID(int id)
{
	this->mID = id;
}

string SkinGame::GetSkinText()
{
	return mSkinText;
}

void SkinGame::SetSkinText(string text)
{
	this->mSkinText = text;
}

bool SkinGame::IsAllowUse()
{
	return mAllowUse;
}

void SkinGame::SetAllowUse(bool allow)
{
	this->mAllowUse = allow;
}

bool SkinGame::IsIssue()
{
	return mIssue;
}

void SkinGame::SetIssue(bool issue)
{
	this->mIssue = issue;
}
