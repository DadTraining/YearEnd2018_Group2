#include "DbContext.h"

sqlite3* DbContext::_dataBase;
std::string DbContext::_path;

bool DbContext::OpenConnect()
{
	_path = cocos2d::FileUtils::getInstance()->getWritablePath() + DATA_BASE_NAME;

	if (sqlite3_open(_path.c_str(), &_dataBase) != SQLITE_OK)
	{
		sqlite3_close(_dataBase);
		return false;
	}
	return true;
}

void DbContext::CloseConnect()
{
	sqlite3_close(_dataBase);
}

bool DbContext::CreateTable()
{
	if (DbContext::OpenConnect())
	{
		int result = sqlite3_exec(_dataBase,
			"create table tbMapLevel(id integer primary key autoincrement, lv integer,star integer,p1 integer,p2 integer,p3 integer,skin integer,score integer,pass boolean,allowplay boolean)"
			, nullptr, nullptr, nullptr);
		int result1 = sqlite3_exec(_dataBase,
			"create table tbSkin(id integer primary key autoincrement,path text,allowuse boolean,isuse boolean)"
			, nullptr, nullptr, nullptr);
		if (result ==0 && result1 ==0)
		{
			return true;
		}
	}
	return false;
}

bool DbContext::InsertData()
{
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,1,0,3,5,7,0,0,'false','true')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,2,0,4,6,8,0,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,3,0,5,7,9,0,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,4,0,5,7,9,4,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,5,0,5,7,9,5,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,6,0,5,7,9,6,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,7,0,5,7,9,7,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,8,0,6,8,10,5,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,9,0,6,8,10,6,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,10,0,6,8,10,7,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,11,0,6,8,10,8,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,12,0,6,8,10,9,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,13,0,7,9,11,4,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,14,0,7,9,11,5,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,15,0,7,9,11,6,0,'false','false')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,16,0,7,9,11,7,0,'false','false')"
		, nullptr, nullptr, nullptr);
	////////////////
	sqlite3_exec(_dataBase,
		"insert into tbSkin values (null,ship/ship.png,'true','true')"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbSkin values (null,ship/ship1.png,'false','false')"
		, nullptr, nullptr, nullptr);
	DbContext::CloseConnect();
	return false;
}


