#include "IntroScene.h"
#include "MapScene.h"
#include "define.h"
#include "ui\CocosGUI.h"


USING_NS_CC;

cocos2d::Size visibleSize;

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

	Page();
	Loading();
	BGMusic();
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

	for (int i = 0; i < 3; i++)
	{
		auto layout = ui::Layout::create();
		layout->setContentSize(pageView->getContentSize());
		auto sprite = Sprite::create("HelloWorld.png");
		sprite->setPosition(Vec2(layout->getSize().width / 2, layout->getSize().height / 2));
		layout->addChild(sprite);
		pageView->addPage(layout);

	}
	pageView->scrollToItem(3);

}

/*Creat Background Music*/
void IntroScene::BGMusic()
{
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(MUSIC_BACKGROUND, true);
	
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
	//button->setScale(BUTTON_PLAY_SCALE);
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
					audio->stopBackgroundMusic();
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





