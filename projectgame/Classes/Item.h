#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"Constants.h"
#include"ui\CocosGUI.h"
#include"Shark.h"
#include<vector>

class Item : public Model
{
private:
	int mTimeStun;
	int mScoreSpend;
	bool mStatusStun;
	cocos2d::Sprite* power_bg;
	cocos2d::ui::LoadingBar* power_loadingBar;
	std::vector<Shark*> mSharkList;

public:
	Item();
	Item(cocos2d::Scene * scene);
	~Item();
	virtual void Update();
	virtual void Init();
	void Behavior();
	void OnClickMenuItem(cocos2d::Ref *sender);
	
	void IncreaseBlood();
	bool StunShark(std::vector<Shark*> sharkList);
	bool KillSharkByBoom(std::vector<Shark*> sharkList);
	void ChangeStatusStun();

};
