#include "Meat.h"

#include "define.h"
#include "Constants.h"

Meat::Meat()
{
}

Meat::Meat(cocos2d::Scene * scene) : Model()
{
	mSprite = cocos2d::Sprite::create(MEAT);
	mSprite->setPosition(-10, -10);
	scene->addChild(mSprite);
	this->mVisible = false;
	mSprite->setVisible(false);
}

Meat::~Meat()
{

}

void Meat::Update()
{

}

void Meat::Init()
{

}

void Meat::setPosForMeat(Shark *shark)
{
	if (shark->GetDirection())
	{
		if (shark->getmSize() == 0.75)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				- shark->GetSprite()->getContentSize().width / 2.5,
				shark->GetPosition().y));
		}

		if (shark->getmSize() == 1)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				- shark->GetSprite()->getContentSize().width / 2,
				shark->GetPosition().y));
		}

		if (shark->getmSize() == 1.25)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				- shark->GetSprite()->getContentSize().width / 1.75,
				shark->GetPosition().y));
		}
	}
	else
	{
		if (shark->getmSize() == 0.75)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				+ shark->GetSprite()->getContentSize().width / 2.5,
				shark->GetPosition().y));
		}

		if (shark->getmSize() == 1)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				+ shark->GetSprite()->getContentSize().width / 2,
				shark->GetPosition().y));
		}

		if (shark->getmSize() == 1.25)
		{
			mSprite->setPosition(cocos2d::Vec2(shark->GetPosition().x
				+ shark->GetSprite()->getContentSize().width / 1.75,
				shark->GetPosition().y));
		}
	}
}

void Meat::isEaten(Shark * shark)
{
	//shark->SetOldStatus();
	shark->SetStatus(SHARK_STATUS_BITE);
	shark->SetAlive(true);
	shark->GetSprite()->stopAllActions();
	auto _animate = cocos2d::Animate::create(CreateAnimation(shark->GetColor(), SHARK_BITE_START,
		SHARK_BITE_FRAME, shark->getDelay()));
	auto repeat = cocos2d::Repeat::create(_animate, 3);
	shark->GetSprite()->runAction(repeat);
}

void Meat::disappear()
{
	setVisible(false);
}

void Meat::setVisible(bool visible)
{
	this->mVisible = visible;
	mSprite->setVisible(visible);
}

