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
	//mSprite->setFlipX(!mLeft);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Ship::onTouchBegan, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scene);

	for (int i = 0; i < 25; i++)
	{
		auto b = new Bullet(scene);
		b->Init();
		listBullet.push_back(b);
	}
	Init();
}

Ship::~Ship()
{

}


void Ship::Update()
{
	if (mUp) {
		mSprite->setPosition(cocos2d::Vec2(GetLocation().x, GetLocation().y + SHIP_SPEED));
		if (GetLocation().y >= Constants::getVisibleSize().height * 9 / 10)
		{
			mUp = false;
		}
	}
	else
	{
		mSprite->setPosition(cocos2d::Vec2(GetLocation().x, GetLocation().y - SHIP_SPEED));
		if (GetLocation().y <= Constants::getVisibleSize().height / 4)
		{
			mUp = true;
		}
	}
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->IsVisible()) {
			listBullet.at(i)->UpdateLocation(Vec2(GetPosition() + Vec2(10, 0)));
		}
		listBullet.at(i)->Update();

	}



	//mFrameBullet++;
	//if (mFrameBullet % 4 == 0) {
	//	for (int i = 0; i < listBullet.size(); i++) {
	//		if (!listBullet.at(i)->IsVisible()) {
	//			listBullet.at(i)->Shoot(mLeft);
	//			listBullet.at(i)->SetVisible(true);
	//			break;
	//		}
	//	}
	//}
}

void Ship::Init()
{

	//this->GetSprite()->setScale(SHIP_SCALE);
	this->SetPosition(cocos2d::Vec2(Constants::getVisibleSize().width / 2, Constants::getVisibleSize().height / 2));
	auto animate = cocos2d::Animate::create(CreateAnimation(SHIP_IMG, 1, SHIP_FRAME, 0.15));
	mSprite->runAction(cocos2d::RepeatForever::create(animate));
}

bool Ship::onTouchBegan(Touch * touch, Event * event)
{
	auto mLocation = touch->getLocation();
	auto size = Constants::getVisibleSize();
	if (mLocation.x > size.width / 2 &&
		mLocation.y > size.height * 2 / 7 &&
		mLocation.y < size.height * 4 / 5
		)
	{
		mLeft = true;
	}
	else if (mLocation.x < size.width / 2 &&
		mLocation.y > size.height * 2 / 7 &&
		mLocation.y < size.height * 4 / 5
		)
	{
		mLeft = false;

	}
	mSprite->setFlipX(mLeft);

	return true;
}

void Ship::onTouchMoved(Touch * touch, Event * event)
{
}

void Ship::onTouchEnded(Touch * touch, Event * event)
{
}

void Ship::ShootColor(std::string color)
{
	for (int i = 0; i < listBullet.size(); i++) {
		if (!listBullet.at(i)->IsVisible()) {
			listBullet.at(i)->Shoot(mLeft);
			listBullet.at(i)->SetVisible(true);
			break;
		}
	}
}

