#pragma once
#include "cocos2d.h"
#include "Model.h"
using namespace cocos2d;
class Bullet : public Model
{
private:
	int mSpeed;
	bool mIsRunRight;

public:
	Bullet(cocos2d::Scene * scene);
	~Bullet();

	/**
	* Shoot bullet to right or to left
	*
	* @param right : true is run to right, false is run to left
	*/
	void Shoot(bool right);

	virtual void Update();
	
	virtual void Init();
	void SetSpeed(int speed);
	int GetSpeed();
	void UpdateLocation(cocos2d::Vec2);
};
