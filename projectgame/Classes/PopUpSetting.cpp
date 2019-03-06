#include "SimpleAudioEngine.h"
#include "PopUpSetting.h"
#include "define.h"
#include "MapScene.h"
#include "GamePlayScene.h"

bool PopupSetting::init()
{
	Popup::init();
	Popup::setBackground();
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		onBGM = true;
	}
	else onBGM = false;

	if (!Constants::isInMap())
	{
		mLabel = cocos2d::Sprite::create(PAUSE);
		setContent();
		checkboxBGM();
		checkboxSFX();
		////////////////////
		auto btnHome = ui::Button::create(BUTTON_HOME);
		btnHome->setPosition(Vec2(-mBackground->getContentSize().width / 7,
			-mBackground->getContentSize().height / 4
			+ mBackground->getContentSize().height / 22));

		btnHome->setScale(0.75);
		mLayer->addChild(btnHome, 1);
		btnHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType touch) {
			switch (touch)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				cocos2d::Director::getInstance()->resume();
				Constants::ReleaseButton();
				Director::getInstance()->replaceScene(MapScene::createScene());
				break;

			}
		});


	}
	else
	{
		mLabel = cocos2d::Sprite::create(SETTING);
		setContent();
		////////////////
		//Add slider of mBgm and mSfx
		sliderBGM();
		sliderSFX();
		mPercentBGM = 50;
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(mPercentBGM / 100);
	}

	return true;
}

void PopupSetting::onExit()
{
	Popup::onExit();
}

void PopupSetting::setContent()
{

	mLabel->setPosition(Vec2(0, mBackground->getContentSize().height / 7));
	mLayer->addChild(mLabel);
	mLayer->setPosition(Constants::getVisibleSize().width / 2, Constants::getVisibleSize().height / 1.7);
	mLabel->setScale(0.75);
	mSfx = cocos2d::Sprite::create(SFX);
	mSfx->setPosition(Vec2(-mBackground->getContentSize().width / 6,
		mLabel->getPosition().y - mBackground->getContentSize().height / 8));
	mLayer->addChild(mSfx);
	mSfx->setScale(0.75);

	mBgm = cocos2d::Sprite::create(BGM);
	mBgm->setPosition(Vec2(mSfx->getPosition().x,
		mSfx->getPosition().y - mBackground->getContentSize().height / 10));
	mLayer->addChild(mBgm);
	mBgm->setScale(0.75);
}

/*Add Slider*/
void PopupSetting::sliderBGM()
{
	auto sliderB = cocos2d::ui::Slider::create();
	sliderB->setPercent(50);
	sliderB->loadBarTexture(SLIDE_BAR_BG);
	sliderB->loadSlidBallTextureNormal(SLIDE_ROUND);
	sliderB->loadProgressBarTexture(SLIDE_BAR_PROGRESS);
	sliderB->setAnchorPoint(Vec2(0, 0.5));
	sliderB->setScale(0.45);

	sliderB->setPosition(Vec2(mBgm->getPosition().x + mBackground->getContentSize().width / 12,
		mBgm->getPosition().y));
	mLayer->addChild(sliderB);

	sliderB->addEventListener([=](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider *_slider = dynamic_cast<ui::Slider*>(sender);
			mPercentBGM = (float)_slider->getPercent();
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(mPercentBGM / 100);
			break;
		}
		default:
			break;
		}
	});
}

void PopupSetting::sliderSFX()
{

	auto sliderS = cocos2d::ui::Slider::create();
	sliderS->setPercent(50);
	sliderS->loadBarTexture(SLIDE_BAR_BG);
	sliderS->loadSlidBallTextureNormal(SLIDE_ROUND);
	sliderS->loadProgressBarTexture(SLIDE_BAR_PROGRESS);
	sliderS->setAnchorPoint(Vec2(0, 0.5));
	sliderS->setScale(0.45);

	sliderS->setPosition(Vec2(mSfx->getPosition().x + mBackground->getContentSize().width / 12,
		mSfx->getPosition().y));
	mLayer->addChild(sliderS);

	sliderS->addEventListener([&](Ref* sender, cocos2d::ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			cocos2d::ui::Slider *_slider = dynamic_cast<ui::Slider*>(sender);
			mPercentSFX = _slider->getPercent();
			break;
		}
		default:
			break;
		}
	});
}

void PopupSetting::checkboxBGM()
{
	checkboxBOn = cocos2d::ui::CheckBox::create(BOX, BOX, BOX_TICK, BOX, BOX);
	checkboxBOn->setPosition(Vec2(mBgm->getPosition().x + mBackground->getContentSize().width / 8,
		mBgm->getPosition().y));
	mLayer->addChild(checkboxBOn);
	checkboxBOn->setSelected(onBGM);

	auto on = cocos2d::Sprite::create(ONOFFSTATE);
	on->setPosition(Vec2(checkboxBOn->getPosition().x + mBackground->getContentSize().width / 8,
		mBgm->getPosition().y));
	mLayer->addChild(on);

		checkboxBOn->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				onBGM = !onBGM;
				if (!onBGM)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				}
				else CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				break;
			default:
				break;
			}
		});
}

void PopupSetting::checkboxSFX()
{
	checkboxSOn = cocos2d::ui::CheckBox::create(BOX, BOX, BOX_TICK, BOX, BOX);
	checkboxSOn->setPosition(Vec2(mSfx->getPosition().x + mBackground->getContentSize().width / 8,
		mSfx->getPosition().y));
	mLayer->addChild(checkboxSOn);
	checkboxSOn->setSelected(onBGM);

	auto on = cocos2d::Sprite::create(ONOFFSTATE);
	on->setPosition(Vec2(checkboxSOn->getPosition().x + mBackground->getContentSize().width / 8,
		mSfx->getPosition().y));
	mLayer->addChild(on);

	checkboxSOn->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			/*onBGM = !onBGM;
			if (!onBGM)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			}
			else CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();*/
			break;
		default:
			break;
		}
	});
}

void PopupSetting::HandlTouch()
{
	Constants::SetEnableAllTouchEventOnMapLevel(true);
	mLayer->setVisible(false);
	int tag = cocos2d::Director::getInstance()->getRunningScene()->getTag();
	cocos2d::log("%d", tag);
	
	cocos2d::Director::getInstance()->resume();
}
