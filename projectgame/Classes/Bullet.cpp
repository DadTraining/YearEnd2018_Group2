#include"Bullet.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"

Bullet::Bullet(cocos2d::Scene * scene) : Model()
{
	mSprite = cocos2d::Sprite::create(BULLET_IMG);
	this->GetSprite()->setScale(0.5);
	
	scene->addChild(mSprite);

	
}

Bullet::~Bullet()
{
	
}

void Bullet::Init()
{
	
	SetVisible(false);
	}
void Bullet::Update()
{

}

void Bullet::ShootRight()
{
	if (IsVisible())
	{
		mSprite->setPosition(GetLocation().x + 5, GetLocation().y);
		if (GetLocation().x > SCREEN_W)
		{
			SetVisible(false);
		}

	}
}

void Bullet::ShootLeft()
{
	if (IsVisible())
	{
		mSprite->setPosition(GetLocation().x - 5, GetLocation().y);
		if (GetLocation().x < 0)
		{
			SetVisible(false);
		}
	}
}



void Bullet::SetSpeed(int speed)
{
	this->mSpeed = speed;

}

int Bullet::GetSpeed()
{
	return this->mSpeed;
}

void Bullet::UpdateLocation(cocos2d::Vec2 location)
{
	mSprite->setPosition(location);
}

