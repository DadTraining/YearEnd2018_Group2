#include"Item.h"
#include"cocos2d.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"


Item::Item(cocos2d::Scene * scene) : Model()
{ 
	
	//CreatItem(scene);
	LoadingBarPower(scene);
	mStatusStun = false;
	mTimeStun = 0;

	
}

Item::~Item()
{
	
}

void Item::Init()
{
	
	
}

void Item::Update()
{
	if (mStatusStun) {
		mTimeStun++;
		if (mTimeStun % 70==0)
		{
			mStatusStun = false;
			mTimeStun = 0;
			ChangeStatusStun();
		}
	}
}


void Item::Behavior()
{

}

void Item::OnClickMenuItem(cocos2d::Ref * sender)
{
	
	

}

void Item::LoadingBarPower(Scene * scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// Loading bar bg
	power_bg = cocos2d::Sprite::create(LOADINGBAR_BG_IMAGE);
	power_bg->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.1));
	power_bg->setScale(LOADING_BAR_SCALE);
	scene->addChild(power_bg);

	//loading bar
	power_loadingBar = ui::LoadingBar::create(LOADINGBAR_IMAGE);
	power_loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	power_loadingBar->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.1));
	power_loadingBar->setScale(LOADING_BAR_SCALE);
	power_loadingBar->setPercent(0);
	scene->addChild(power_loadingBar,999);

	/*auto updateloadingbar = CallFunc::create([=]() {
		if (loadingBar->getPercent() < 100)
		{
			loadingBar->setPercent(loadingBar->getPercent() + 1);
		}
	});
	auto sequenceloadingbar = Sequence::create(updateloadingbar, DelayTime::create(0.1), nullptr);
	auto repeat = Repeat::create(sequenceloadingbar, 100);
	loadingBar->runAction(repeat);*/
}

void Item::CreatItem(Scene * scene)
{
	auto SizeScene = Director::getInstance()->getVisibleSize();
	
	buttonBrick = ui::Button::create(ITEM_BRICK_IMAGE);
	buttonBrick->setPosition(Vec2(Constants::getVisibleSize().width * 0.85, Constants::getVisibleSize().height * 0.95));
	buttonBrick->setScale(ITEM_SCAlE);
	
	buttonHP = ui::Button::create(ITEM_HP_IMAGE);
	buttonHP->setScale(ITEM_SCAlE);
	buttonHP->setPosition(Vec2(Constants::getVisibleSize().width * 0.9, Constants::getVisibleSize().height * 0.95));
	buttonHP->addClickEventListener([=](Ref* event)
	{  
		IncreaseBlood();
	});
	buttonBoom = ui::Button::create(ITEM_BOOM_IMAGE);
	buttonBoom->setScale(ITEM_SCAlE);
	buttonBoom->setPosition(Vec2(Constants::getVisibleSize().width * 0.95, Constants::getVisibleSize().height * 0.95));

	scene->addChild(buttonBrick);
	scene->addChild(buttonHP);
	scene->addChild(buttonBoom);
}

void Item::IncreaseBlood()
{
	
	power_loadingBar->setPercent(power_loadingBar->getPercent() + 10);
}

void Item::StunShark(std::vector<Shark*> sharkList)
{
	mSharkList = sharkList;
	for (int i = 0; i < sharkList.size(); i++)
	{
			for (int j = 0; j < 8; j++)
			{
				sharkList[i]->UnUpdate(sharkList[i]->GetPosition());
			}
	}
	mStatusStun = true;
}

void Item::KillSharkByBoom(std::vector<Shark*> sharkList)
{
	
}

void Item::ChangeStatusStun()
{
	for (int i = 0; i < mSharkList.size(); i++)
	{
		mSharkList[i]->SetOldStatus();
	}
}




