#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"Constants.h"
#include"ui\CocosGUI.h"
#include"Shark.h"
#include <vector>
using namespace cocos2d;
class Item : public Model
{
private:
	int mTimeStun;
	int mScoreSpend;
	bool mStatusStun;
	Sprite* power_bg;
	cocos2d::ui::LoadingBar* power_loadingBar;
	std::vector<Shark*> mSharkList;

public:
	Item(cocos2d::Scene * scene);
	~Item();
	virtual void Update();
	virtual void Init();
	void Behavior();
	void OnClickMenuItem(cocos2d::Ref *sender);
	
	void IncreaseBlood();
	void StunShark(std::vector<Shark*> sharkList);
	void KillSharkByBoom(std::vector<Shark*> sharkList);
	void ChangeStatusStun();


};
