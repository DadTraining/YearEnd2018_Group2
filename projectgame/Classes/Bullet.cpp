#include"Bullet.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"

Bullet::Bullet(cocos2d::Scene * scene) : Model()
{
	// Set variable
	mIsRunRight = true;

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
void Bullet::Shoot(bool right)
{
	mIsRunRight = right;
}
void Bullet::Update()
{
	if (IsVisible())
	{
		if (mIsRunRight)
		{
			mSprite->setPosition(GetLocation().x + 5, GetLocation().y);
			if (GetLocation().x > SCREEN_W)
			{
				SetVisible(false);
			}
		}
		else 
		{
			mSprite->setPosition(GetLocation().x - 5, GetLocation().y);
			if (GetLocation().x < - 10)
			{
				SetVisible(false);
			}
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

