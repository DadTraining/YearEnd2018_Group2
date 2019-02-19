#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"Cable.h"

class Shark : public Model
{
protected:
	float mSize;
	float mDelay;
	bool mIsBitten;
	bool mMoveToLeft;
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
	void BiteAnimation();
	void SwimAnimation();
	void Move();
	void RunAwayAnimation();

	virtual void Update();
	virtual void Init();
	bool IsBitten();
	void setIsBitten(bool bitten);
	bool BittenCable(Cable *cable);

	std::string GetColor();
};

