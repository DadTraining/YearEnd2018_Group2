#pragma once
#include "cocos2d.h"
#include"Bullet.h"
#include"Ship.h"
#include"Item.h"
#include"Cable.h"
#include"Shark.h"


using namespace std;

class GamePlayScene : public cocos2d::Scene
{
private:
	std::vector<Shark*> sharkList;
	Ship * ship;
	Cable *cable;	
	Vec2 mLocation;
	cocos2d::PhysicsWorld* mPhysicsWorld;
	std::vector<ui::Button*> listItem;
	
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
	
	void deleteShark();
	CREATE_FUNC(GamePlayScene);
};

