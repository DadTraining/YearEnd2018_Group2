#include"Ship.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"

Ship::Ship(cocos2d::Scene * scene)
{
	mSprite = cocos2d::Sprite::create();
	scene->addChild(mSprite, 999);
	mUp = true;
	mLeft = false;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		auto b = new Bullet(scene);
		//b->Init();
		b->SetTag(100 + i);
		listBullet.push_back(b);
	}
	Init();



}

Ship::~Ship()
{

}


void Ship::Update()
{
	/*if (mUp) {
		mSprite->setPosition(cocos2d::Vec2(GetLocation().x, GetLocation().y + SHIP_SPEED));
		if (GetLocation().y >= Constants::getVisibleSize().height * 9 / 10)
		{
			mUp = false;
		}
	}
	else
	{
		mSprite->setPosition(cocos2d::Vec2(GetLocation().x, GetLocation().y - SHIP_SPEED));
		if (GetLocation().y <= Constants::getVisibleSize().height *3/10)
		{
			mUp = true;
		}
	}*/
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet.at(i)->Update();
	}

}

void Ship::Init()
{

	this->SetPosition(cocos2d::Vec2(Constants::getVisibleSize().width / 2, Constants::getVisibleSize().height / 2));
	auto animate = cocos2d::Animate::create(CreateAnimation(SHIP_IMG, 1, SHIP_FRAME, 0.15));
	mSprite->runAction(cocos2d::RepeatForever::create(animate));
}

void Ship::leftOrRight(bool direction)
{
	//direction = true is right
	if (direction)
	{
		if (!mLeft)
		{
			mLeft = true;
			mSprite->setFlipX(mLeft);
		}
	}
	else
	{
		if (mLeft)
		{
			mLeft = false;
			mSprite->setFlipX(mLeft);
		}
	}
}

bool Ship::getDirection()
{
	return mLeft;
}

void Ship::ShootColor(int color)
{
	for (int i = 0; i < listBullet.size(); i++) {
		auto bullet = listBullet.at(i);
		if (!bullet->IsVisible()) {
			bullet->Shoot(mLeft);
			bullet->UpdateLocation(Vec2(mSprite->getPosition()));
			bullet->SetVisible(true);
			bullet->Init();
			bullet->SetColor(color);
			break;
		}
	}
}

void Ship::Collision(std::vector<Shark*> sharks, int sharkTag, int bulletTag)
{
	auto shark = sharks[sharkTag - 1];
	auto bullet = listBullet[bulletTag - 100];
	if (shark->IsAlive() && bullet->IsAlive())
	{
		if (shark->GetColor() == bullet->GetColor())
		{
			shark->Killed();
			bullet->SetVisible(false);
		}
		else
		{
			bullet->SetVisible(false);
		}
	}
	
}





