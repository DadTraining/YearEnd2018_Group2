#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Shark.h"


class Cable : public Model
{
private:	

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
	void CheckSharkNearCable(std::vector<Shark*> sharks, bool directionShip);
	void SetTarget(cocos2d::Vec2 pos, bool vis);

};