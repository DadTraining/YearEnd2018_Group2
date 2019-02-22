#pragma once
#include "cocos2d.h"
#include "Model.h"
using namespace cocos2d;
class Meat : public Model
{
private:
	
public:
	Meat(cocos2d::Scene * scene);
	~Meat();
	virtual void Update();
	virtual void Init();
};
