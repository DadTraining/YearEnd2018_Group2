#include"Cable.h"
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"Model.h"
#include"define.h"
#include "Constants.h"
#include"GamePlayScene.h"
#include"Shark.h"
#include<time.h>

Cable::Cable(cocos2d::Scene * scene) 
{
	CreatCable(scene);
	LoadingBar(scene);	
	mHp = 100;
}

Cable::~Cable()
{

}

void Cable::Bitten()
{
	mHp -= 5;
	loadingBar->setPercent(mHp);
	log("%d", mHp);
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

void Cable::LoadingBar(Scene * scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//icon HP
	auto iconhp = cocos2d::Sprite::create(ICON_HP);
	iconhp->setPosition(cocos2d::Vec2(visibleSize.width / 16, visibleSize.height / 1.07));
	iconhp->setScale(0.3);
	scene->addChild(iconhp,999);
	//loadingbarwhite
    loadingbar_white = cocos2d::Sprite::create(HP_CABLEWHITE);
	loadingbar_white->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.07));
	loadingbar_white->setScale(0.3);
	scene->addChild(loadingbar_white,999);

	//loading bar
    loadingBar = ui::LoadingBar::create(HP_CABLERED);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPosition(cocos2d::Vec2(visibleSize.width / 5, visibleSize.height / 1.07));
	loadingBar->setScale(0.3);
	loadingBar->setPercent(100);
	scene->addChild(loadingBar,999);
}

void Cable::CreatCable(Scene *scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	mSprite = cocos2d::Sprite::create(CABLE_IMG);
	
	mSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));
	mSprite->setScaleY(Constants::setScaleSprite(Constants::getVisibleSize().height, 1, mSprite->getContentSize().height));
	scene->addChild(mSprite);
}

void Cable::EffectCable()
{
	/*cocos2d::Waves* waveEffect = cocos2d::Waves::create(2.0, cocos2d::Size(20, 20), 5, 25,false,true);	  
	mSprite->runAction(waveEffect);*/
	auto fadeOut = FadeOut::create(0.5);
	auto fadein = FadeIn::create(0.5);
	auto sequen = Sequence::create(fadeOut, fadein,fadeOut->clone(),fadein->clone(), nullptr);
	mSprite->runAction(sequen);
	srand(time(NULL));


}



