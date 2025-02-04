#pragma once
#include "cocos2d.h"
#include "sqlite3.h"
#include "define.h"
#include "MapLevel.h"
#include "SkinGame.h"

class DbContext
{
protected:
	static sqlite3* _dataBase;
	static std::string _path;
public:
	static bool OpenConnect();
	static void CloseConnect();
	static bool CreateTable();
	static bool InsertData();

	static std::vector<MapLevel*> GetAllMapLevel();

	static bool UpdateDataMap(int id, int star, int score);

	static int GetItem(int index);


	/*
		index : 1 is brick
				2 is tool repair
				3 is electric
	*/
	static void UpdateItem(int index,int items);
	static int GetScore();
	static void UpdateScore(int score);
	/*
		index = 1 is sound effect
		index = 2 is background music
	*/
	static int GetSound(int index);
	static void UpdateSound(int sf, int bg);

	static std::vector<SkinGame*> GetListShip();
	static void UpdateSkinShip(int id);
	static std::string GetNameSkin(int id);
};
