#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Shark.h"

class Meat : public Model
{
private:
	
public:
	Meat();
	Meat(cocos2d::Scene * scene);
	~Meat();

	virtual void Update();
	virtual void Init();

	void setPosForMeat(Shark *shark);
	void isEaten(Shark *shark);
	
	void disappear();
	void setVisible(bool visible);
};
