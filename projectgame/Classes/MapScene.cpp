#include"Model.h"
#include"MapScene.h"
#include"define.h"


Size _visibleSize;

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


	_visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create(IMG_MAPSCENE);

	background->setPosition(Vec2(_visibleSize.width / 2 + origin.x,
		_visibleSize.height / 2 + origin.y));
	
	addChild(background, -1);

	initLevel();
	initPopUpLevel();

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
		mListButton.push_back(button);


		///////////////////
		//set position for button
		switch (i)
		{
		case 1:
		{
			button->setPosition(Vec2(_visibleSize.width / 6.31,
				_visibleSize.height * 3.07 / 4));
			break;
		}
		case 2:
		{
			button->setPosition(Vec2(_visibleSize.width / 4.1,
				_visibleSize.height / 1.52));
			break;
		}
		case 3:
		{
			button->setPosition(Vec2(_visibleSize.width / 4.65,
				_visibleSize.height / 2.02));
			break;
		}
		case 4:
		{
			button->setPosition(Vec2(_visibleSize.width / 7.55,
				_visibleSize.height / 2.6));
			break;
		}
		case 5:
		{
			button->setPosition(Vec2(_visibleSize.width / 5.46,
				_visibleSize.height / 4.15));
			break;
		}
		case 6:
		{
			button->setPosition(Vec2(_visibleSize.width / 3.37,
				_visibleSize.height / 4.2));
			break;
		}
		case 7:
		{
			button->setPosition(Vec2(_visibleSize.width / 2.65,
				_visibleSize.height / 2.695));
			break;
		}
		case 8:
		{
			button->setPosition(Vec2(_visibleSize.width / 2.61,
				_visibleSize.height / 1.83));
			break;
		}
		case 9:
		{
			button->setPosition(Vec2(_visibleSize.width / 2.1,
				_visibleSize.height / 1.4));
			break;
		}
		default:
			break;
		}

		this->addChild(button);



		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:

				CCLOG("%i", i);
				mListPlay[i - 1]->getLayer()->setVisible(true);
				
				break;
			}
		});
	}
}

/*Init level*/
void MapScene::initLevel()
{
	for (int i = 0; i < 9; i++)
	{
		MapLevel *level = new MapLevel();
		level->SetLevel(i + 1);
		level->SetStar(0);
		mListLevel.push_back(level);
	}
}

/*Init Popup level*/
void MapScene::initPopUpLevel()
{
	/////////////////
	//creat popup play
	

	for (int i = 0; i < 9; i++)
	{
		PopupPlay *popup = PopupPlay::create();
		this->addChild(popup, 3);

		popup->getLayer()->setVisible(false);

		//popup->setVisible(false);
		popup->setLevel(mListLevel[i]->GetLevel(), mListLevel[i]->GetStar());
		mListPlay.push_back(popup);
	}

}
