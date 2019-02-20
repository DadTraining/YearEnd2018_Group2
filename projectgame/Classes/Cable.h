#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Model.h"
#include"Bullet.h"
#include<vector>
using namespace std;
using namespace cocos2d;
class Cable : public Model
{
private:	
	Sprite * loadingbar_white;
	ui::LoadingBar * loadingBar;
	int mHp;
public:
	Cable(cocos2d::Scene * scene);
	~Cable();
	void Bitten();
	void Armor();

	virtual void Update();
	virtual void Init();
	void LoadingBar(Scene *scene);
	void CreatCable(Scene * scene);
	void EffectCable();
	
};