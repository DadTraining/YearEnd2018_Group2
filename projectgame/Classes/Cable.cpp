#include "Cable.h"
#include "define.h"
#include "Constants.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

#pragma region declare
cocos2d::Sprite* loadingbar_white;
ui::LoadingBar * loadingBar;
cocos2d::Sprite* mTargetSprite;
#pragma endregion


Cable::Cable(cocos2d::Scene * scene)
{
#pragma region create cable

	auto visibleSize = Director::getInstance()->getVisibleSize();
	mSprite = cocos2d::Sprite::create(CABLE_IMG);

	mSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	mSprite->setScaleY(Constants::setScaleSprite(Constants::getVisibleSize().height, 1, mSprite->getContentSize().height));

	auto width = mSprite->getContentSize().width / 4;
	auto height = mSprite->getContentSize().height;
	auto cableBody = cocos2d::PhysicsBody::createBox(Size(width, height), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(3, 3));
	cableBody->setDynamic(false);
	cableBody->setCategoryBitmask(0x01);
	cableBody->setContactTestBitmask(true);
	this->SetTag(0);
	mSprite->setPhysicsBody(cableBody);

	scene->addChild(mSprite);
#pragma endregion

#pragma region loadingbar

	//auto visibleSize = Constants::getVisibleSize();
	//icon HP
	auto iconhp = cocos2d::Sprite::create(ICON_HP);
	iconhp->setPosition(cocos2d::Vec2(visibleSize.width / 16, visibleSize.height / 1.07));
	iconhp->setScale(0.3);
	scene->addChild(iconhp, 999);
	//loadingbarwhite
	loadingbar_white = cocos2d::Sprite::create(HP_CABLEWHITE);
	loadingbar_white->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.07));
	loadingbar_white->setScale(0.3);
	scene->addChild(loadingbar_white, 999);

	//loading bar
	loadingBar = ui::LoadingBar::create(HP_CABLERED);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.07));
	loadingBar->setScale(0.3);
	loadingBar->setPercent(100);
	scene->addChild(loadingBar, 999);
#pragma endregion

	mHp = 100;

	mTargetSprite = cocos2d::Sprite::create("target/target_1.png");
	mTargetSprite->setVisible(false);
	//mTargetSprite->setPosition(300, 300);
	scene->addChild(mTargetSprite, 999);
	TargetAnimation();
}

Cable::~Cable()
{

}

void Cable::Bitten()
{
	mHp -= 5;
	loadingBar->setPercent(mHp);
	//log("%d", mHp);
}

void Cable::Armor()
{
}


void Cable::Update()
{

}

void Cable::Init()
{
}

void Cable::EffectCable()
{
	/*cocos2d::Waves* waveEffect = cocos2d::Waves::create(2.0, cocos2d::Size(20, 20), 5, 25,false,true);
	mSprite->runAction(waveEffect);*/

	auto fadeOut = FadeOut::create(0.1);
	auto fadein = FadeIn::create(0.1);
	auto sequen = Sequence::create(fadeOut, fadein, fadeOut->clone(), fadein->clone(), nullptr);
	mSprite->runAction(sequen);
	//srand(time(NULL));


}

void Cable::TargetAnimation()
{
	auto animate = cocos2d::Animate::create(
		this->CreateAnimation(TARGET_SHARK, 1, 2, 0.1)
	);
	mTargetSprite->runAction(
		cocos2d::RepeatForever::create(animate)
	);

}

void Cable::CheckSharkNearCable(std::vector<Shark*> sharks, Ship* ship)
{
	float _minPos = MIN_POSITION;
	Shark* sh;
	for (int i = 0; i < sharks.size(); i++)
	{
		auto sk = sharks[i];
		if (sk->GetDirection() == ship->GetDirection() && sk->IsVisible())
		{
			float pos;
			if (ship->GetDirection())
			{
				pos = (float)sk->GetLocation().x - this->GetLocation().x;
				mTargetSprite->setAnchorPoint(cocos2d::Vec2(1, 0.5));
			}
			else
			{
				pos = (float) this->GetLocation().x - sk->GetLocation().x;
				mTargetSprite->setAnchorPoint(cocos2d::Vec2(0, 0.5));
			}
			if (pos < _minPos)
			{
				_minPos = pos;
				sh = sk;
			}
		}
	}
	if (_minPos < MIN_POSITION && sh != nullptr)
	{
		SetTarget(sh->GetLocation(), true);
		ship->ShipMove(sh->GetLocation().y);
	}
	else
	{
		SetTarget(cocos2d::Vec2(0, 0), false);
	}

}

void Cable::SetTarget(cocos2d::Vec2 pos, bool vis)
{
	try
	{
		mTargetSprite->setVisible(vis);
		mTargetSprite->setPosition(pos);
	}
	catch (const std::exception&)
	{
		CCLOG("fail set sprite target");
	}
}



