#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopupEndGame.h"
#include "PopUpSetting.h"
#include "define.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

bool PopupEndGame::init()
{
	Popup::init();
	Popup::setBackground();

	///////////////
	//Button home
	auto btnHome = ui::Button::create(BUTTON_MAP_PLAY);
	btnHome->setPosition(Vec2(0, -mBackground->getContentSize().height / 4
								+ mBackground->getContentSize().height / 22));
	
	mLayer->addChild(btnHome, 1);
	btnHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Constants::ReleaseButton();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});

	////////////////
	//Button next level
	auto btnSetting = ui::Button::create(BUTTON_SETTING);
	btnSetting->setPosition(Vec2(- mBackground->getContentSize().width / 7, 
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnSetting->setScale(0.75);
	mLayer->addChild(btnSetting, 1);
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
		switch (t)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			PopupSetting *popup = PopupSetting::create();
			this->addChild(popup, 3);
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
