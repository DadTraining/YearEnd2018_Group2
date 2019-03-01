#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopupEndGame.h"
#include "PopUpSetting.h"
#include "MapScene.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include"InfoMap.h"

USING_NS_CC;

bool PopupEndGame::init()
{
	Popup::init();
	Popup::setBackground();
	//Button replay
	auto btnRePlay = ui::Button::create(BUTTON_REPLAY_IMG);
	btnRePlay->setPosition(Vec2(- mBackground->getContentSize().width / 7,
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnRePlay->setScale(0.75);
	mLayer->addChild(btnRePlay, 1);
	btnRePlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->resume();
			Constants::ReleaseButton();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});
	//Button next
	auto btnNextLV = ui::Button::create(BUTTON_MAP_PLAY);
	btnNextLV->setPosition(Vec2(0, -mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	mLayer->addChild(btnNextLV, 1);
	btnNextLV->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			CCLOG("%d", InfoMap::getMapLevel());
			cocos2d::Director::getInstance()->resume();
			Constants::SetPhase(InfoMap::getMapLevel());
			Constants::ReleaseButton();
			auto callback = cocos2d::CallFunc::create([=]() {
				Director::getInstance()->replaceScene(TransitionFadeTR::create(0, MapScene::createScene()));
			});
			auto callback2 = cocos2d::CallFunc::create([=]() {
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.5, GamePlayScene::createScene()));
			});
			auto seq = cocos2d::Sequence::create(
				callback,
				callback2,
				nullptr
			);
			this->runAction(seq);
			break;
		}
	});

	return true;
}

void PopupEndGame::onExit()
{
	Popup::onExit();
}

/*Set level popup*/
void PopupEndGame::setLevel(int numLevel, int numStars)
{
	std::string png = ".png", stars = "stars", path = "map/", l = "Level", le, st;
	char cLevel[20] = { 0 };
	sprintf(cLevel, "map/Level%d.png", numLevel);
	auto lv = Sprite::create(cLevel);
	lv->setPosition(Vec2(0, mBackground->getContentSize().height / 5.5));
	mLayer->addChild(lv);

	char cStars = '0' + numStars;
	st = path + cStars + stars + png;
	auto star = Sprite::create(st);
	star->setPosition(Vec2(0, mBackground->getContentSize().height / 17));
	star->setScale(0.5);
	mLayer->addChild(star);
}

void PopupEndGame::HandlTouch()
{
	Constants::ReleaseButton();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1, MapScene::createScene()));

}

	


	
