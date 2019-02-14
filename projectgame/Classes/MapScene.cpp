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
	button1->setPosition(Vec2(visibleSize.width/6.3, visibleSize.height/1.3));	
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;			
		case ui::Widget::TouchEventType::ENDED:			
			// dialog
			auto bt1 = Sprite::create(DIALOG_MAP);
			bt1->setScale(0.2);
			bt1->setPosition(Vec2(SCREEN_W/2,SCREEN_H/2));			
			addChild(bt1);
			auto Lable1 = Sprite::create(Lable_1);
			Lable1->setScale(0.5);
			Lable1->setPosition(Vec2(SCREEN_W/2, SCREEN_H/1.55));
			addChild(Lable1);
			auto IMG_Star = Sprite::create(IMG_STAR);
			IMG_Star->setScale(0.5);
			IMG_Star->setPosition(Vec2(SCREEN_W/2, SCREEN_H/1.85));
			addChild(IMG_Star);


			//button play
			auto button_play = ui::Button::create(BUTTON_PLAY);
			button_play->setScale(0.7);
			button_play->setPosition(Vec2(SCREEN_W/2,SCREEN_H/2.5));
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
			button_exit->setPosition(Vec2(SCREEN_W/1.62, SCREEN_H/1.55));
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
	button2->setPosition(Vec2(visibleSize.width/4.1, visibleSize.height/1.52));
	button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type2) {
		switch (type2)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt2 = Sprite::create(DIALOG_MAP);
			bt2->setScale(0.2);
			//bt2->setPosition(Vec2(SCREEN_W/2, SCREEN_H/2));
			bt2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			addChild(bt2,100);
			auto Lable2 = Sprite::create(Lable_2);
			Lable2->setScale(0.5);
			Lable2->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.55));
			addChild(Lable2);
			auto IMG_Star = Sprite::create(IMG_STAR);
			IMG_Star->setScale(0.5);
			IMG_Star->setPosition(Vec2(SCREEN_W / 2, SCREEN_H/1.85));
			addChild(IMG_Star);

			//button play
			auto button_play2 = ui::Button::create(BUTTON_PLAY);
			button_play2->setScale(0.7);
			button_play2->setPosition(Vec2(SCREEN_W / 2, SCREEN_H/2.5));
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
			button_exit2->setPosition(Vec2(SCREEN_W / 1.62, SCREEN_H / 1.55));
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
	button3->setPosition(Vec2(visibleSize.width/4.5, visibleSize.height/2));
	button3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type3) {
		switch (type3)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt3 = Sprite::create(DIALOG_MAP);
			bt3->setScale(0.2);
			bt3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2));
			addChild(bt3);
			auto Lable3 = Sprite::create(Lable_3);
			Lable3->setScale(0.5);
			Lable3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.55));
			addChild(Lable3);
			auto IMG_Star3 = Sprite::create(IMG_STAR);
			IMG_Star3->setScale(0.5);
			IMG_Star3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.85));
			addChild(IMG_Star3);

			//button play
			auto button_play3 = ui::Button::create(BUTTON_PLAY);
			button_play3->setScale(0.7);
			button_play3->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2.5));
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
			button_exit3->setPosition(Vec2(SCREEN_W / 1.62, SCREEN_H / 1.55));
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
	button4->setPosition(Vec2(visibleSize.width / 7.6, visibleSize.height / 2.6));
	button4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type4) {
		switch (type4)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt4 = Sprite::create(DIALOG_MAP);
			bt4->setScale(0.2);
			bt4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2));
			addChild(bt4);
			auto Lable4 = Sprite::create(Lable_4);
			Lable4->setScale(0.5);
			Lable4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.55));
			addChild(Lable4);
			auto IMG_Star4 = Sprite::create(IMG_STAR);
			IMG_Star4->setScale(0.5);
			IMG_Star4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.85));
			addChild(IMG_Star4);

			//button play
			auto button_play4 = ui::Button::create(BUTTON_PLAY);
			button_play4->setScale(0.7);
			button_play4->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2.5));
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
			button_exit4->setPosition(Vec2(SCREEN_W / 1.62, SCREEN_H / 1.55));
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
	button5->setPosition(Vec2(visibleSize.width / 5.5, visibleSize.height / 4.1));
	button5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type5) {
		switch (type5)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			auto bt5 = Sprite::create(DIALOG_MAP);
			bt5->setScale(0.2);
			bt5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H /2));
			addChild(bt5);
			auto Lable5 = Sprite::create(Lable_5);
			Lable5->setScale(0.5);
			Lable5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.55));
			addChild(Lable5);
			auto IMG_Star5 = Sprite::create(IMG_STAR);
			IMG_Star5->setScale(0.5);
			IMG_Star5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 1.85));
			addChild(IMG_Star5);

			//button play
			auto button_play5 = ui::Button::create(BUTTON_PLAY);
			button_play5->setScale(0.7);
			button_play5->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2.5));
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
			button_exit5->setPosition(Vec2(SCREEN_W / 1.62, SCREEN_H / 1.55));
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

	//--------------level 6 ---------------
	auto button6 = ui::Button::create(BUTTON_6);
	button6->setScale(0.8);
	button6->setPosition(Vec2(visibleSize.width / 3.4, visibleSize.height / 4));
	button6->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type6) {
		switch (type6)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		}
	});
	addChild(button6);

	//----------------------level 7-----------------
	auto button7 = ui::Button::create(BUTTON_7);
	button7->setScale(0.8);
	button7->setPosition(Vec2(visibleSize.width / 2.65, visibleSize.height / 2.7));
	button7->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type7) {
		switch (type7)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		}
	});
	addChild(button7);

	//----------------------level 8-----------------

	auto button8 = ui::Button::create(BUTTON_8);
	button8->setScale(0.8);
	button8->setPosition(Vec2(visibleSize.width / 2.65, visibleSize.height / 1.75));
	button8->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type8) {
		switch (type8)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		}
	});
	addChild(button8);
	return true;
}

