#include "Cable.h"
#include "define.h"
#include "Constants.h"
#include "ui/CocosGUI.h"


#pragma region declare
cocos2d::Sprite* loadingbar_white;
ui::LoadingBar * loadingBar;
ui::LoadingBar * loadingBarGreen;
cocos2d::Sprite* mTargetSprite;
#pragma endregion


Cable::Cable(cocos2d::Scene * scene)
{
	auto visibleSize = Constants::getVisibleSize();
	mHp = 100;
	CreateCable(scene);
	LoadingBar(scene);


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
	loadingBarGreen->setPercent(mHp);
	if (mHp >= 0 && mHp < 20) {
		loadingBarGreen->loadTexture(HP_CABLERED);
		EffectLoadingBar();
	}

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

void Cable::LoadingBar(cocos2d::Scene * scene)
{
	auto visibleSize = Constants::getVisibleSize();
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

	//loading bar green
	loadingBarGreen = ui::LoadingBar::create(HP_CABLEGREEN);
	loadingBarGreen->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBarGreen->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.07));
	loadingBarGreen->setScale(0.3);
	loadingBarGreen->setPercent(100);
	scene->addChild(loadingBarGreen, 999);
}

void Cable::CreateCable(cocos2d::Scene * scene)
{

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

void Cable::EffectLoadingBar()
{
	auto fadeOut_LoadingBar = FadeOut::create(0.5);
	auto fadeIn_LoadingBar = FadeIn::create(0.5);
	auto sequen_LoadingBar = Sequence::create(fadeOut_LoadingBar, fadeIn_LoadingBar, fadeOut_LoadingBar->clone(), fadeIn_LoadingBar->clone(), nullptr);
	loadingBarGreen->runAction(sequen_LoadingBar);

	/*auto fadeOut_LoadingBarWhite = FadeOut::create(0.5);
	auto fadeIn_LoadingBarWhite = FadeIn::create(0.5);
	auto sequen_LoadingBarWhite = Sequence::create(fadeOut_LoadingBarWhite, fadeIn_LoadingBarWhite, fadeOut_LoadingBarWhite->clone(), fadeIn_LoadingBarWhite->clone());
	loadingbar_white->runAction(sequen_LoadingBarWhite);*/
	
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



