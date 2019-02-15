#pragma once
#include "cocos2d.h"
#include "Model.h"
#include"Bullet.h"
#include<vector>
using namespace std;
using namespace cocos2d;
class Ship : public Model
{
private:
	bool mUp;
	bool mLeft;
	vector<Bullet*> listBullet;
	int mFrameBullet;
	

public:
	Ship(cocos2d::Scene * scene);
	~Ship();



	virtual void Update();
	virtual void Init();
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);


	void ShootColor(std::string color);

};