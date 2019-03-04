#pragma once
#include "cocos2d.h"
#include "sqlite3.h"
#include "define.h"
#include "MapLevel.h"

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

};
