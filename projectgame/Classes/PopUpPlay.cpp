#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "PopUpPlay.h"
#include "PopUpSetting.h"
#include "define.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

bool PopupPlay::init()
{
	Popup::init();
	Popup::setBackground();

	///////////////
	//Button play
	auto btnPlay = ui::Button::create(BUTTON_MAP_PLAY);
	btnPlay->setPosition(Vec2(0, -mBackground->getContentSize().height / 4
								+ mBackground->getContentSize().height / 22));
	
	mLayer->addChild(btnPlay, 1);
	btnPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON, false);
			break;
		case ui::Widget::TouchEventType::ENDED:
			Constants::ReleaseButton();
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_BACKGROUND_PLAY, true);
			
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GamePlayScene::createScene()));
			break;
		}
	});

	////////////////
	//Button setting
	auto btnSetting = ui::Button::create(BUTTON_SETTING);
	btnSetting->setPosition(Vec2(- mBackground->getContentSize().width / 7, 
		-mBackground->getContentSize().height / 4
		+ mBackground->getContentSize().height / 22));

	btnSetting->setScale(0.75);
	mLayer->addChild(btnSetting, 1);
	btnSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
		switch (touch)
		{
		case ui::Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON, false);
			break;
		case ui::Widget::TouchEventType::ENDED:
			PopupSetting *popup = PopupSetting::create();
			this->addChild(popup, 3);
			//mLayer->setVisible(false);
			break;
		}
	});
	return true;
}

void PopupPlay::onExit()
{
	Popup::onExit();
}

/*Set level popup*/
void PopupPlay::setLevel(int numLevel, int numStars)
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

void PopupPlay::HandlTouch()
{

	Constants::SetEnableAllTouchEventOnMapLevel(true);
	for (int i = 0; i < Constants::GetListMap().size(); i++)
	{
		auto map = Constants::GetListMap().at(i);
		Constants::SetEnableTouchEvent(i, map->isAllowPlay());
	}
	mLayer->setVisible(false);
	cocos2d::Director::getInstance()->resume();

}
