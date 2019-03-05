#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MapLevel.h"
#include <vector>
#include "InfoMap.h"
#include "SimpleAudioEngine.h"
#include "define.h"


class Constants 
{
private:
	//static cocos2d::Size mSize;
	static cocos2d::Vector<cocos2d::ui::Button*> listButton;
	static std::vector<MapLevel*> listMap;
	//in gameplay
	static bool inMap;
	static bool onBGM, onSFX;
	

public:
	//background music
	/*static CocosDenshion::SimpleAudioEngine *bgmMap;
	static CocosDenshion::SimpleAudioEngine *bgmPlay;*/

	static cocos2d::Size getVisibleSize();
	static float setScaleSprite(float whichSize,float expectSize, float realSize);

	static void AddButtonIntoMapLevel(cocos2d::ui::Button* btn);
	static void SetEnableTouchEvent(int index,bool enable);
	static void SetEnableAllTouchEventOnMapLevel(bool enable);

	static  std::vector<MapLevel*> GetListMap();
	static void AddMapIntoList(MapLevel* map);

	static void SetPhase(int index);
	static void ReleaseButton();
	static bool ListButtonIsEmpty();

	static void EndGame(int lv, int star, bool pass, int score);

	static void setInMap(bool in);
	static bool isInMap();

	static void setOnBGM(bool on);
	static void changeOnBGM();
	static bool getOnBGM();

};

