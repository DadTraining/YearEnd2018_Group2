#include"Bullet.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"
#include "MyBodyParser.h"

Bullet::Bullet(cocos2d::Scene * scene) : Model()
{
	mSprite = cocos2d::Sprite::create("bullet/bullet.png");
	//this->GetSprite()->setScale(0.5);
	SetVisible(false);
	scene->addChild(mSprite);
}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(mSprite, BULLET_BODY, cocos2d::PhysicsMaterial(1, 1, 0));
	if (spriteBody != nullptr)
	{
		spriteBody->setDynamic(false);
		mSprite->setPhysicsBody(spriteBody);
		mSprite->getPhysicsBody()->setCategoryBitmask(0x01);
		mSprite->getPhysicsBody()->setContactTestBitmask(true);
	}
}
void Bullet::Update()
{
	if (IsVisible())
	{
		if (mIsRunRight)
		{
			mSprite->setPosition(GetPosition().x + BULLET_SPEED, GetPosition().y);
			if (GetPosition().x > SCREEN_W)
			{
				SetVisible(false);
			}
		}
		else
		{
			mSprite->setPosition(GetPosition().x - BULLET_SPEED, GetPosition().y);
			if (GetPosition().x < -10)
			{
				SetVisible(false);
			}
		}
	}

}

void Bullet::ShootRight()
{
	if (IsVisible())
	{
		mSprite->setPosition(GetLocation().x + BULLET_SPEED, GetLocation().y);
		if (GetLocation().x > Constants::getVisibleSize().width)
		{
			SetVisible(false);
		}

	}
}

void Bullet::ShootLeft()
{
	if (IsVisible())
	{
		mSprite->setPosition(GetLocation().x - BULLET_SPEED, GetLocation().y);
		if (GetLocation().x < 0)
		{
			SetVisible(false);
		}
	}
}

void Bullet::Shoot(bool right)
{
	mIsRunRight = right;
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

void Bullet::SetColor(int color)
{
	mSprite->stopAllActions();
	mColor = color;
	switch (color)
	{
	case 1: //red
		
		mSprite->runAction(cocos2d::RepeatForever::create(
			cocos2d::Animate::create(CreateAnimation(BULLET_SHOOT_RED_IMG, 1, 3, 0.15)))
		);
		break;
	case 2://blue
		mSprite->runAction(cocos2d::RepeatForever::create(
			cocos2d::Animate::create(CreateAnimation(BULLET_SHOOT_BLUE_IMG, 1, 3, 0.15)))
		);
		break;
	case 3://yellow
		mSprite->runAction(cocos2d::RepeatForever::create(
			cocos2d::Animate::create(CreateAnimation(BULLET_SHOOT_YELLOW_IMG, 1, 3, 0.15)))
		);
		break;
	case 4://black

		break;
	case 5://white

		break;
	default:
		break;
	}
}

std::string Bullet::GetColor()
{
	std::string color;
	switch (mColor)
	{
	case 1://red
		color = SHARK_RED;
		break;
	case 2: // blue
		color = SHARK_BLUE;
		break;
	case 3://yellow
		color = SHARK_YELLOW;
		break;
	case 4://black
		break;
	case 5://white
		break;
	case 6:
		break;
	default:
		break;
	}
	return color;
}

