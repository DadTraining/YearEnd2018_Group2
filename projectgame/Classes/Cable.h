#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Shark.h"
#include "Ship.h"


class Cable : public Model
{
private:	
	Sprite * loadingbar_white;
	//ui::LoadingBar * loadingBar;
	ui::LoadingBar * loadingBarGreen;
	int mHp;

public:
	Cable(cocos2d::Scene * scene);
	~Cable();
	void Bitten();
	void Armor();

	virtual void Update();
	virtual void Init();
	void EffectCable();
	
	void TargetAnimation();
	void CheckSharkNearCable(std::vector<Shark*> sharks,Ship* ship);
	void SetTarget(cocos2d::Vec2 pos, bool vis);

	void EffectLoadingBar();
};