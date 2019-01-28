#pragma once
#include "cocos2d.h"

class Shark
{
protected:
	float mSize;
	std::string mColor;
	int mTotalColor;
	float mSpeed;
	int mDamage;
	std::string mStatus;

public:
	Shark();
	Shark(cocos2d::Scene* scene);
	Shark(const Shark * shark);
	virtual ~Shark();

	void Damaged();
	void Killed();
	void Angry();
	void Normal();
	void RunAway();
	void ChangeDirection();
	void Clone();

	virtual void Update();
	virtual void Init();
};

