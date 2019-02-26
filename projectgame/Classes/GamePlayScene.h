#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Ship.h"
#include "Item.h"
#include "Cable.h"
#include "Shark.h"
#include "Meat.h"

class GamePlayScene : public cocos2d::Scene
{
private:
	Ship* ship;
	Cable* cable;	
	Vec2 mLocation;
	cocos2d::PhysicsWorld* mPhysicsWorld;
	std::vector<ui::Button*> listItem;
	std::vector<ui::Button*> mSettingPause;
	std::vector<Shark*> sharkList;
	int callBackAlive;
	int timeLeft;
	std::vector<Meat*> meatList;
	cocos2d::ui::Button *whiteButton;
	int pressed;
	int countDownButtonMeat;
	int countDownMeat;
	
	double mScore;
	Label *mLabelScore;
public:
	static cocos2d::Scene* createScene();
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init() override;

	void update(float delta) override;
	// implement the "static create()" method manually
	void SharkAliveCallBack();

	bool onTouchBegan(Touch *touch, Event *event);
	bool onContactBegin(PhysicsContact& contact);

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { mPhysicsWorld = world; }

	bool CheckColisionSharkWithCable(int sharkTag);

	void WinGame();
	void LoseGame();


	//////
	void initMeatList(Scene *scene, std::vector<Shark*> sharkList);
	void meatDone();

	void setPressWhiteButton(bool pres);
	void SetEnableAllTouchEventOnScene(bool enable);
	CREATE_FUNC(GamePlayScene);
};

