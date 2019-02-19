#include"Model.h"
#include"MapScene.h"
#include"define.h"


Size visibleSize;

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


	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create(IMG_MAPSCENE);

	background->setPosition(Vec2(visibleSize.width / 2 + origin.x,
							visibleSize.height / 2 + origin.y));
	//background->setAnchorPoint(Vec2::ZERO);
	//background->setScale(0.5);
	addChild(background, -1);

	initLevel();

	
	setListButton();
	return true;
}

void MapScene::setListButton()
{
	std::string png = ".png", normal, pressed, num = ".1", path = "map/";
	char c; //get number of picture

	for (int i = 1; i < LIST_BUTTON_MAX; i++)
	{
		////////////////
		//add button to list
		c = '0' + i;
		normal = path + c + png;
		pressed = path + c + num + png;
		auto button = ui::Button::create(normal, pressed);
		listButton.push_back(button);

		
		///////////////////
		//set position for button
		switch (i)
		{
		case 1:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 6.8, 
				visibleSize.height*3/4 + visibleSize.height/9));
			break;
		}
		case 2:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 4.3, 
				visibleSize.height / 1.54 + visibleSize.height / 9));
			break;
		}
		case 3:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 4.9, 
				visibleSize.height / 2 + +visibleSize.height / 9));
			break;
		}
		case 4:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 8.6, 
				visibleSize.height / 2.6 + visibleSize.height / 9));
			break;
		}
		case 5:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 5.9, 
				visibleSize.height / 3.9 + visibleSize.height / 9));
			break;
		}
		case 6:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 3.4, 
				visibleSize.height / 3.9 + visibleSize.height / 9));
			break;
		}
		case 7:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 2.65, 
				visibleSize.height / 2.67 + visibleSize.height / 9));
			break;
		}
		case 8:
		{
			button->setScale(1.2);
			button->setPosition(Vec2(visibleSize.width / 2.65, 
				visibleSize.height / 1.83 + visibleSize.height / 9));
			break;
		}
		default:
			break;
		}
		
		this->addChild(button);

		/////////////////
		//creat popup play
		PopupPlay *popup = PopupPlay::create();
		this->addChild(popup, 3);
		
		//popup->setLevel(listLevel[i]->GetLevel(), listLevel[i]->GetStar());
		popup->setVisible(false);

		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				popup->setVisible(true);
				popup->setLevel(listLevel[i - 1]->GetLevel(), listLevel[i - 1]->GetStar());
				break;
			}
		});
	}
}

/*Init level*/
void MapScene::initLevel()
{
	for (int i = 0; i < 8; i++)
	{
		MapLevel *level = new MapLevel();
		level->SetLevel(i + 1);
		level->SetStar(0);
		listLevel.push_back(level);
	}
}
