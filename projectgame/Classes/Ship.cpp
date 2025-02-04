#include"Ship.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"
#include "InfoMap.h"
#include "InfoMap.h"


Ship::Ship(cocos2d::Scene * scene)
{

	mSprite = cocos2d::Sprite::create(Constants::GetNameShip());
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
	mLeft = !direction;
	mSprite->setFlipX(mLeft);
}


void Ship::ShootColor(int color)
{

	for (int i = 0; i < listBullet.size(); i++) {
		auto bullet = listBullet.at(i);
		if (!bullet->IsVisible()) {
			bullet->Shoot(mLeft);

			if (mLeft) {
				bullet->UpdateLocation(Vec2(mSprite->getPosition() + Vec2(mSprite->getContentSize().width * 5 / 13, mSprite->getContentSize().height*-1.5 / 84)));
			}
			else {
				bullet->UpdateLocation(Vec2(mSprite->getPosition() - Vec2(mSprite->getContentSize().width * 4 / 13, mSprite->getContentSize().height * 4 / 84)));
			}


			bullet->SetVisible(true);

			bullet->Init();
			bullet->SetColor(color);
			break;
		}
	}
}

bool Ship::Collision(std::vector<Shark*> sharks, int sharkTag, int bulletTag)
{

	auto shark = sharks[sharkTag - 1];
	auto bullet = listBullet[bulletTag - 100];
	if (shark->IsAlive() && bullet->IsAlive())
	{
		auto result = shark->CheckColor(bullet->GetColor());
		if (result && shark->GetTotalColor() == 1)
		{
			shark->Killed();
			bullet->SetVisible(false);
			return true;
		}
		else if (result && shark->GetTotalColor() != 1)
		{
			bullet->SetVisible(false);
			if (shark->EnoughColor())
			{
				shark->Killed();
			}
			return true;
		}
		else
		{
			bullet->SetVisible(false);
			return false;
		}
	}
	return true;

}

void Ship::SetPositionY(float y)
{
	mSprite->setPositionY(y);
}

void Ship::ShipMove(float posY)
{
	float _posY = this->GetLocation().y;
	if (_posY < posY - SHIP_SPEED)
	{
		this->SetPositionY(_posY + SHIP_SPEED);
	}
	else if (_posY > posY + SHIP_SPEED)
	{
		this->SetPositionY(_posY - SHIP_SPEED);
	}
}





