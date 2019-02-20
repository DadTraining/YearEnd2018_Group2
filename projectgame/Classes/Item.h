#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"Constants.h"
#include"ui\CocosGUI.h"
#include"GamePlayScene.h"
#include"Shark.h"
#include<vector>
using namespace cocos2d;
class Item : public Model
{
private:
	int mTimeStun;
	bool mStatusStun;
	int mScoreSpend;

	cocos2d::ui::Button *buttonBrick;
	cocos2d::ui::Button *buttonHP;
	cocos2d::ui::Button *buttonBoom;

	Sprite * power_bg;
	cocos2d::ui::LoadingBar *power_loadingBar;
	std::vector<Shark*> mSharkList;


public:
	Item(cocos2d::Scene * scene);
	~Item();
	virtual void Update();
	virtual void Init();
	void Behavior();
	void OnClickMenuItem(cocos2d::Ref *sender);
	void LoadingBarPower(Scene * scene);
	void CreatItem(Scene * scene);
	void IncreaseBlood();
	void StunShark(std::vector<Shark*> sharkList);
	void KillSharkByBoom(std::vector<Shark*> sharkList);
	void ChangeStatusStun();


};
