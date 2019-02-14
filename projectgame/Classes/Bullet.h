#pragma once
#include "cocos2d.h"
#include "Model.h"
using namespace cocos2d;
class Bullet : public Model
{
private:
	int mSpeed;

public:
	Bullet(cocos2d::Scene * scene);
	~Bullet();
	virtual void Update();
	virtual void ShootRight();
	virtual void ShootLeft();
	virtual void Init();
	void SetSpeed(int speed);
	int GetSpeed();
	void UpdateLocation(cocos2d::Vec2);
};
