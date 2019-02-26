#pragma once
#include "cocos2d.h"
#include "Shark.h"
#include "Model.h"
#include "Meat.h"
#include "Bullet.h"
#include <vector>

class Ship : public Model
{
private:
	bool mUp;
	bool mLeft;
	int mFrameBullet;
	std::vector<Bullet*> listBullet;

public:
	Ship(cocos2d::Scene * scene);
	~Ship();

	virtual void Update();
	virtual void Init();
	
	void leftOrRight(bool direction);

	void ShootColor(int color);

	void Collision(std::vector<Shark*> sharks,int sharkTag,int bulletTag);

	bool GetDirection() {
		return mLeft;
	}

	void SetPositionY(float y);

	void ShipMove(float posY);


};