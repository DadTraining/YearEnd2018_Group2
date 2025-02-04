#include "Cable.h"
#include "define.h"
#include "Constants.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

#pragma region declare

#pragma endregion


Cable::Cable(cocos2d::Scene * scene)
{
#pragma region create cable

	auto visibleSize = Director::getInstance()->getVisibleSize();
	mSprite = cocos2d::Sprite::create(CABLE_IMG);

	mSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));

	//mSprite->setScaleY(Constants::setScaleSprite(Constants::getVisibleSize().height, 1, mSprite->getContentSize().height));

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
	mHp = 100;
	//loadingbarwhite
	loadingbar_white = cocos2d::Sprite::create(HP_WHITE);
	loadingbar_white->setAnchorPoint(cocos2d::Vec2(0,0.5));
	loadingbar_white->setPosition(cocos2d::Vec2(15, visibleSize.height / 5.35));
	
	scene->addChild(loadingbar_white, 999);

	//loading bar green
	loadingBarGreen = ui::LoadingBar::create(HP_GREEN);
	loadingBarGreen->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBarGreen->setAnchorPoint(cocos2d::Vec2(0,0.5));
	loadingBarGreen->setPosition(cocos2d::Vec2(loadingbar_white->getPosition()));
	loadingBarGreen->setPercent(mHp);
	scene->addChild(loadingBarGreen, 999);
#pragma endregion

	

	mTargetSprite = cocos2d::Sprite::create("target/target_1.png");
	mTargetSprite->setVisible(false);
	//mTargetSprite->setPosition(300, 300);
	scene->addChild(mTargetSprite,101);
	TargetAnimation();

}

Cable::~Cable()
{

}

void Cable::Bitten()
{
	mHp -= 10;
	loadingBarGreen->setPercent(mHp);
	if (mHp < 25)
	{
      EffectLoadingBar();
	}
	if (mHp<80 && mHp >= 25)
	{
	Cable::BrokenAnimation(2);
	}
	else if(mHp<25)
	{
	Cable::BrokenAnimation(0.5);
	}

	//log("%d", mHp);
}

void Cable::Armor()
{
}


void Cable::Update()
{
	
	if ( mHp < 25)
	{
		loadingBarGreen->loadTexture(HP_RED);
		//EffectLoadingBar();
	}
	if(mHp>=25)
	{
		loadingBarGreen->loadTexture(HP_GREEN); 		
	}
//	CCLOG("%d", mHp);

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
}

void Cable::EffectLoadingBar()
{
	auto fadeOut_LoadingBar = FadeOut::create(0.5);
	auto fadeIn_LoadingBar = FadeIn::create(0.5);
	auto sequen_LoadingBar = Sequence::create(fadeOut_LoadingBar, fadeIn_LoadingBar, fadeOut_LoadingBar->clone(), fadeIn_LoadingBar->clone(), nullptr);
	loadingBarGreen->runAction(sequen_LoadingBar);
}

bool Cable::IncreaseHP()
{	
	if (Constants::GetHps()<=0)
	{
		return false;
	}
	mHp += 20;
	if (mHp>100)
	{
		mHp = 100;
	}
	loadingBarGreen->setPercent(mHp);
	Constants::SetHps(Constants::GetHps() - 1);
	if (Constants::GetHps() <= 0)
	{
		return false;
	}
	return true;
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
	if (
		_minPos < MIN_POSITION 
		&& sh != nullptr
		//&& sh->GetStatus() != SHARK_STATUS_RUNAWAY_ANIMATION
		)
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

int Cable::GetHP()
{
	return mHp;
}

void Cable::BrokenAnimation(float delay)
{
	mSprite->stopAllActions();
	auto animate = cocos2d::Animate::create(Model::CreateAnimation(CABLE_BROKEN, 1, 4, 0.2));
	auto callback = cocos2d::CallFunc::create([=]() {
		
	});

	auto seq = cocos2d::Sequence::create(
		animate,
		DelayTime::create(delay),
		nullptr
	);
	auto repeat = cocos2d::RepeatForever::create(seq);
	mSprite->runAction(repeat);
}



