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
	
	//-----------------------level 1------------------------
	auto button1 = ui::Button::create(BUTTON_1);
	button1->setScale(0.8);
	button1->setPosition(Vec2(visibleSize.width-860, visibleSize.height-135));	
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;			
		case ui::Widget::TouchEventType::ENDED:			
			// dialog
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
	addChild(button1);


	// -------------------level 2--------------------
	
	auto button2 = ui::Button::create(BUTTON_2);
	button2->setScale(0.8);
	button2->setPosition(Vec2(visibleSize.width -772, visibleSize.height - 200));
	button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type2) {
		switch (type2)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt2 = Sprite::create(DIALOG_MAP);
			bt2->setScale(0.2);
			bt2->setPosition(Vec2(SCREEN_W - 512, SCREEN_H - 288));
			addChild(bt2);

			auto IMG_Star = Sprite::create(IMG_STAR);
			IMG_Star->setScale(0.5);
			IMG_Star->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 245));
			addChild(IMG_Star);

			//button play
			auto button_play2 = ui::Button::create(BUTTON_PLAY);
			button_play2->setScale(0.7);
			button_play2->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 335));
			button_play2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType t) {
				switch (t)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_play2);

			//button exit dialog
			auto button_exit2 = ui::Button::create(BUTTON_EXIT);
			button_exit2->setScale(0.35);
			button_exit2->setPosition(Vec2(SCREEN_W - 396, SCREEN_H - 202));
			button_exit2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType i) {
				switch (i)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_exit2);

			break;
		}

	});
	addChild(button2);

	// -------------------------level 3---------------------------
	 

	return true;
}

