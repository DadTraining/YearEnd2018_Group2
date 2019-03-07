#include "IntroScene.h"
#include "MapScene.h"
#include "define.h"
#include "ui\CocosGUI.h"
#include "Shark.h"
#include "MapLevel.h"
#include "InfoMap.h"
#include "Constants.h"
#include "DbContext.h"
#include "ShopScene.h"



USING_NS_CC;


Scene* IntroScene::createScene()
{
	return IntroScene::create();
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = cocos2d::Sprite::create(WATER);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, -1);

	Page();
	Loading();
	AddDataBase();
	BGMusic();
	//LoadGame();
	
	return true;
}

/*Creat PageView to show guidance*/
void IntroScene::Page()
{
	auto pageView = ui::PageView::create();
	pageView->setContentSize(Size(visibleSize.width, visibleSize.height));
	pageView->setBounceEnabled(true);
	pageView->setTouchEnabled(true);
	pageView->setAnchorPoint(Vec2(0.5, 0.5));
	pageView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + visibleSize.height / 7));
	this->addChild(pageView);

	for (int i = 2; i < 4; i++)
	{
		char normal[20] = { 0 };
		sprintf(normal, "intro/%d.png", i);
		auto layout = ui::Layout::create();
		layout->setContentSize(pageView->getContentSize());
	    auto sprite = Sprite::create(normal);
		sprite->setPosition(Vec2(layout->getSize().width / 2, layout->getSize().height / 2));
		layout->addChild(sprite);
		pageView->addPage(layout);

	}
    pageView->scrollToItem(3);

}

/*Create Background Music*/
void IntroScene::BGMusic()
{
	bgmMap = CocosDenshion::SimpleAudioEngine::getInstance();
	bgmMap->preloadBackgroundMusic(MUSIC_BACKGROUND_MAP);
	bgmMap->preloadBackgroundMusic(MUSIC_BACKGROUND_PLAY);
	bgmMap->preloadEffect(SFX_BUTTON_BULLET);
	bgmMap->preloadEffect(SFX_BUTTON);

	if (Constants::getOnBGM())
	{
		bgmMap->playBackgroundMusic(MUSIC_BACKGROUND_MAP, true);
	}
	//bgmMap->setBackgroundMusicVolume(0.5f);
}

void IntroScene::AddDataBase()
{
	if (DbContext::CreateTable())
	{
		DbContext::InsertData();
	}

	auto listMap = DbContext::GetAllMapLevel();

	for (int i = 0; i < listMap.size(); i++)
	{
		Constants::AddMapIntoList(listMap.at(i));
	}

	Constants::SetTotalCoin(DbContext::GetScore());
	Constants::setOnSFX(DbContext::GetSound(1)==1? true:false);
	Constants::setOnBGM(DbContext::GetSound(2)==1? true:false);

	Constants::LoadSkinGame();
}

void IntroScene::LoadGame()
{
}

/*Create LoadingBar*/
void IntroScene::Loading()
{
	static auto loadingBarBG = Sprite::create(LOADING_BAR_BACKGROUND);
	loadingBarBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 7));
	loadingBarBG->setVisible(true);
	addChild(loadingBarBG, 2);

	static auto loadingBar = ui::LoadingBar::create(LOADING_BAR);
	loadingBar->setPercent(0);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPosition(loadingBarBG->getPosition());
	loadingBar->setVisible(true);
	addChild(loadingBar, 2);

	//////////////
	//button play
	static auto button = ui::Button::create(BUTTON_PLAY);
	button->setPosition(loadingBar->getPosition());

	button->setVisible(false);
	this->addChild(button, 3);
	loadingBar->setPercent(70);
	auto updateLoadingBar = CallFunc::create([=]() {
		if (loadingBar->getPercent() < 100)
		{
			loadingBar->setPercent(loadingBar->getPercent() + 1);
		}

		if (loadingBar->getPercent() == 100)
		{
			loadingBarBG->setVisible(false);
			loadingBar->setVisible(false);

			//////////////////////
			//button play appear when loading finish
			button->setVisible(true);
			button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BUTTON, false);
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1, MapScene::createScene()));
					break;
				}

				default:
					break;
				}
			});
		}
	});

	auto sequenceRunUpdateLoadingBar = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.1f));
	auto repeatLoad = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	loadingBar->runAction(repeatLoad);
	
}





