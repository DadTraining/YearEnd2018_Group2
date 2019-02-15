#pragma once
#include "cocos2d.h"
#include "Model.h"
using namespace cocos2d;
class Item : public Model
{
private:
 int mScoreSpend;
public:
	Item(cocos2d::Scene * scene);
	~Item();
	virtual void Update();
	virtual void Init();
	void Behavior();

};
