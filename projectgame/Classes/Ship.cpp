#include"Ship.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"
#include "InfoMap.h"
#include "InfoMap.h"


Ship::Ship(cocos2d::Scene * scene)
{

	mSprite = cocos2d::Sprite::create(SHIP_IMG);
	scene->addChild(mSprite, 100);
	mUp = true;
	mLeft = false;
	Init();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		Bullet* b = new Bullet(scene);
		b->SetTag(i + 100);
		listBullet.push_back(b);
	}

}

Ship::~Ship()
{

}


void Ship::Update()
{
	
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet.at(i)->Update();
	}

}

void Ship::Init()
{

	this->SetPosition(cocos2d::Vec2(Constants::getVisibleSize().width / 2, Constants::getVisibleSize().height / 2));
	
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


void Ship::ShootColor(int color)
{

	for (int i = 0; i < listBullet.size(); i++) {
		auto bullet = listBullet.at(i);
		if (!bullet->IsVisible()) {
			bullet->Shoot(mLeft);
		
		  if (mLeft) {
				//bullet->UpdateLocation(Vec2(mSprite->getPosition()+Vec2(50,-15)));
				bullet->UpdateLocation(Vec2(mSprite->getPosition() + Vec2(mSprite->getContentSize().width*5/13,mSprite->getContentSize().height*-1.5/84 )));
			}
			else {
				//bullet->UpdateLocation(Vec2(mSprite->getPosition()-Vec2(40,4)));
				bullet->UpdateLocation(Vec2(mSprite->getPosition() - Vec2(mSprite->getContentSize().width * 4 / 13, mSprite->getContentSize().height*4/84)));
			}

			
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

void Ship::SetPositionY(float y)
{
	mSprite->setPositionY(y);
}

void Ship::ShipMove(float posY)
{
	float _posY = this->GetLocation().y;
	if (_posY < posY -10)
	{
		this->SetPositionY(_posY + SHIP_SPEED);
	}
	else if (_posY  > posY +10 )
	{
		this->SetPositionY(_posY - SHIP_SPEED);
	}
}





