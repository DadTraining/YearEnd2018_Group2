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
	static bool pause;
	

	static int brick;
	static int hp;
	static int boom;
	static int totalCoin;
	static int totalStar;

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

	static bool BuyBooms();
	static bool BuyBricks();
	static bool BuyHps();
	static int GetBooms();
	static int GetHps();
	static int GetBricks();
	static void SetBooms(int num);
	static void SetHps(int num);
	static void SetBricks(int num);
	static void RefreshItem();

	static void SetTotalCoin(int coins);
	static int GetTotalCoin();
	static int GetTotalStar();
	static void SetTotalStar(int star);
	


};

