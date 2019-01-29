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
	 
	auto button3 = ui::Button::create(BUTTON_3);
	button3->setScale(0.7);
	button3->setPosition(Vec2(visibleSize.width - 800, visibleSize.height - 288));
	button3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type3) {
		switch (type3)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt3 = Sprite::create(DIALOG_MAP);
			bt3->setScale(0.2);
			bt3->setPosition(Vec2(SCREEN_W - 512, SCREEN_H - 288));
			addChild(bt3);

			auto IMG_Star3 = Sprite::create(IMG_STAR);
			IMG_Star3->setScale(0.5);
			IMG_Star3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 245));
			addChild(IMG_Star3);

			//button play
			auto button_play3 = ui::Button::create(BUTTON_PLAY);
			button_play3->setScale(0.7);
			button_play3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 335));
			button_play3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typepl) {
				switch (typepl)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_play3);

			//button exit dialog
			auto button_exit3 = ui::Button::create(BUTTON_EXIT);
			button_exit3->setScale(0.35);
			button_exit3->setPosition(Vec2(SCREEN_W - 396, SCREEN_H - 202));
			button_exit3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType i) {
				switch (i)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_exit3);

			break;
		}

	});
	addChild(button3);

	//---------------------level 4---------------------------

	auto button4 = ui::Button::create(BUTTON_4);
	button4->setScale(0.8);
	button4->setPosition(Vec2(visibleSize.width - 890, visibleSize.height - 352));
	button4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type4) {
		switch (type4)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt4 = Sprite::create(DIALOG_MAP);
			bt4->setScale(0.2);
			bt4->setPosition(Vec2(SCREEN_W - 512, SCREEN_H - 288));
			addChild(bt4);

			auto IMG_Star4 = Sprite::create(IMG_STAR);
			IMG_Star4->setScale(0.5);
			IMG_Star4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 245));
			addChild(IMG_Star4);

			//button play
			auto button_play4 = ui::Button::create(BUTTON_PLAY);
			button_play4->setScale(0.7);
			button_play4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 335));
			button_play4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typepl) {
				switch (typepl)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_play4);

			//button exit dialog
			auto button_exit4 = ui::Button::create(BUTTON_EXIT);
			button_exit4->setScale(0.35);
			button_exit4->setPosition(Vec2(SCREEN_W - 396, SCREEN_H - 202));
			button_exit4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType i) {
				switch (i)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_exit4);

			break;
		}

	});
	addChild(button4);

	// -------------------------level 5------------------------
	auto button5 = ui::Button::create(BUTTON_5);
	button5->setScale(0.8);
	button5->setPosition(Vec2(visibleSize.width - 838, visibleSize.height - 435));
	button5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type5) {
		switch (type5)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt5 = Sprite::create(DIALOG_MAP);
			bt5->setScale(0.2);
			bt5->setPosition(Vec2(SCREEN_W - 512, SCREEN_H - 288));
			addChild(bt5);

			auto IMG_Star5 = Sprite::create(IMG_STAR);
			IMG_Star5->setScale(0.5);
			IMG_Star5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 245));
			addChild(IMG_Star5);

			//button play
			auto button_play5 = ui::Button::create(BUTTON_PLAY);
			button_play5->setScale(0.7);
			button_play5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H - 335));
			button_play5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType typepl) {
				switch (typepl)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_play5);

			//button exit dialog
			auto button_exit5 = ui::Button::create(BUTTON_EXIT);
			button_exit5->setScale(0.35);
			button_exit5->setPosition(Vec2(SCREEN_W - 396, SCREEN_H - 202));
			button_exit5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType i) {
				switch (i)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					break;
				}
			});

			addChild(button_exit5);

			break;
		}

	});
	addChild(button5);

	//
	return true;
}

