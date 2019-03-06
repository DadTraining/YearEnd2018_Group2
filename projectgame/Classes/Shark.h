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
	int mTotalDuplicate;
	int mScore;
	std::string mColor;
	std::string mColor_1st;
	std::string mColor_2nd;
	std::string mStatus;
	std::string mOldStatus;
	cocos2d::Sprite* mStunSprite;
	cocos2d::Sprite* color_1st;
	cocos2d::Sprite* color_2nd;
	bool mDuplicateColor1;
	bool mDuplicateColor2;


public:
	
	Shark();
	Shark(cocos2d::Scene* scene);
	Shark(const Shark * shark);
	virtual ~Shark();
	void DamagedElectronic();
	void StunAnimation();
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
	void CallBackStatus();
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
	void SetStun(bool vis);
	void AddStun(cocos2d::Scene* scene);
	void SetPhysicsBody();
	void SharkSingleSkin();
	void SetNumSkinForShark(int num);
	void SharkMultiSkin();
	bool CheckColor(std::string color);
	void SetPositionCheckColor();
	bool EnoughColor();
	void setShowColorVisible();

};

