#include"Model.h"
#include"MapScene.h"
#include"define.h"
#include<iostream>
#include"ui\CocosGUI.h"

Scene* MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create(IMG_MAPSCENE);
	background->setPosition(SCREEN_W / 2, SCREEN_H / 2);
	background->setScale(1.03);
	addChild(background);

	auto button = ui::Button::create(BUTTON_1);
	button->setPosition(Vec2(visibleSize.width-860, visibleSize.height-135));	
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;			
		case ui::Widget::TouchEventType::ENDED:			
			
			auto bt1 = Sprite::create(DIALOG_MAP);
			bt1->setScale(0.2);
			bt1->setPosition(Vec2(SCREEN_W-512,SCREEN_H-288));
			addChild(bt1);

			auto IMG_Star = Sprite::create(IMG_STAR);
			IMG_Star->setScale(0.5);
			IMG_Star->setPosition(Vec2(SCREEN_W/2, SCREEN_H-245));
			addChild(IMG_Star);

			//button play
			auto button_play = ui::Button::create(BUTTON_PLAY);
			button_play->setScale(0.7);
			button_play->setPosition(Vec2(SCREEN_W/2,SCREEN_H-335));
			button_play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
				switch (t)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_play);

			//button exit dialog
			auto button_exit = ui::Button::create(BUTTON_EXIT);
			button_exit->setScale(0.35);
			button_exit->setPosition(Vec2(SCREEN_W -396, SCREEN_H - 202));
			button_exit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType i) {
				switch (i)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_exit);

			break;
		}
		
	});
	addChild(button);
	
	return true;
}

