#pragma once
#include "cocos2d.h"
#include "Model.h"



class Shark : public Model
{
protected:
	float mSize;
	float mDelay;
	float mSpeed;
	bool mIsBitten;
	bool mMoveToLeft;
	int mTotalColor;
	int mScore;
	std::string mColor;
	std::string mStatus;
	std::string mOldStatus;

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
	void Clone(Shark* shark);
	void BiteAnimation();
	void SwimAnimation();
	void Move();
	void UnMove(cocos2d::Vec2 pos);
	void RunAwayAnimation();
	virtual void Update();
	void UnUpdate(cocos2d::Vec2 pos);
	virtual void Init();
	void SetStatus(std::string status);
	void SetOldStatus();
	void setIsBitten(bool bitten);

	bool IsBitten();
	std::string GetColor();
	bool GetDirection();
	std::string GetStatus();
	std::string GetOldStatus();
	float GetDelay();
	float GetMSize();
	float GetSpeed();
	int GetTotalColor();
	int GetScore();

	void SetPhysicsBody();
};

