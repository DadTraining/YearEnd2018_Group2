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
			"create table tbMapLevel(id integer primary key autoincrement, lv integer,star integer,p1 integer,p2 integer,p3 integer,skin integer,score integer,pass integer,allowplay integer,threestar integer,twostar integer)"
			, nullptr, nullptr, nullptr);
		int result1 = sqlite3_exec(_dataBase,
			"create table tbSkin(id integer primary key autoincrement,path text,allowuse boolean,isuse boolean)"
			, nullptr, nullptr, nullptr);
		int result2 = sqlite3_exec(_dataBase,
			"create table tbItem(id integer primary key autoincrement,itembrick integer,itemtool integer,itemelectric integer)"
			, nullptr, nullptr, nullptr);
		int result3 = sqlite3_exec(_dataBase,
			"create table tbScore(id integer primary key autoincrement,score integer)"
			, nullptr, nullptr, nullptr);
		int result4 = sqlite3_exec(_dataBase,
			"create table tbSound(id integer primary key autoincrement,sound integer,bgm integer)"
			, nullptr, nullptr, nullptr);
		if (result == 0 && result1 == 0 && result2 ==0 && result3 == 0 && result4 ==0)
		{
			return true;
		}
	}
	return false;
}

bool DbContext::InsertData()
{
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,1,0,3,5,7,0,0,0,1,280,150)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,2,0,4,6,8,0,0,0,1,500,150)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,3,0,5,7,9,0,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,4,0,5,7,9,5,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,5,0,5,7,9,7,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,6,0,5,7,9,9,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,7,0,5,7,9,11,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,8,0,6,8,10,13,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,9,0,6,8,10,15,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,10,0,6,8,10,17,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,11,0,6,8,10,19,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,12,0,6,8,10,20,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,13,0,7,9,11,21,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,14,0,7,9,11,22,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,15,0,7,9,11,23,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbMapLevel values (null,16,0,7,9,11,24,0,0,1,400,200)"
		, nullptr, nullptr, nullptr);
	////////////////
	sqlite3_exec(_dataBase,
		"insert into tbSkin values (null,'ship/ship.png',1,1)"
		, nullptr, nullptr, nullptr);
	sqlite3_exec(_dataBase,
		"insert into tbSkin values (null,'ship/ship1.png',0,0)"
		, nullptr, nullptr, nullptr);
	///////////////
	sqlite3_exec(_dataBase,
		"insert into tbItem values (null,3,3,300)"
		, nullptr, nullptr, nullptr);
	/////
	sqlite3_exec(_dataBase,
		"insert into tbScore values (null,1000)"
		, nullptr, nullptr, nullptr);
	/////
	sqlite3_exec(_dataBase,
		"insert into tbSound values (null,1,1)"
		, nullptr, nullptr, nullptr);

	DbContext::CloseConnect();
	return false;
}

std::vector<MapLevel*> DbContext::GetAllMapLevel()
{
	std::vector<MapLevel*> mapLevels;
	DbContext::OpenConnect();
	sqlite3_stmt* stmt = nullptr;

	sqlite3_prepare_v2(_dataBase, "SELECT * FROM tbMapLevel", -1, &stmt, nullptr);

	while (true)
	{
		int result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			int lv = sqlite3_column_int(stmt, 1);
			int st = sqlite3_column_int(stmt, 2);
			int p1 = sqlite3_column_int(stmt, 3);
			int p2 = sqlite3_column_int(stmt, 4);
			int p3 = sqlite3_column_int(stmt, 5);
			int sk = sqlite3_column_int(stmt, 6);
			int sc = sqlite3_column_int(stmt, 7);
			bool wasplay = (sqlite3_column_int(stmt, 8) == 1) ? true : false;
			bool allow = (sqlite3_column_int(stmt, 9) == 1) ? true : false;

			MapLevel* mlv = new MapLevel(
				lv,st,p1,p2,p3,sk,sc,wasplay,allow
				);
			mapLevels.push_back(mlv);
		}
		else
		{
			break;
		}
	}
	DbContext::CloseConnect();
	return mapLevels;
}

bool DbContext::UpdateDataMap(int id, int star, int score)
{
	std::string sql = "Update tbMapLevel SET star =" + std::to_string(star);
	sql.append(",score="+ std::to_string(score));

	sql.append(",pass=" + std::to_string(1));

	sql.append(" Where id =" + std::to_string(id));

	std::string sql1 = "Update tbMapLevel SET ";
	sql1.append("allowplay=" + std::to_string(1));
	sql1.append(" Where id =" + std::to_string(id+1));

	DbContext::OpenConnect();
	sqlite3_exec(_dataBase, sql.c_str(), NULL, NULL, NULL);
	sqlite3_exec(_dataBase, sql1.c_str(), NULL, NULL, NULL);
	DbContext::CloseConnect();
	return false;
}

int DbContext::GetItem(int index)
{
	int _x;
	DbContext::OpenConnect();
	sqlite3_stmt* stmt = nullptr;

	sqlite3_prepare_v2(_dataBase, "SELECT * FROM tbItem", -1, &stmt, nullptr);

	while (true)
	{
		int result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			_x = sqlite3_column_int(stmt, index);
		}
		else
		{
			break;
		}
	}
	DbContext::CloseConnect();
	return _x;
}

void DbContext::UpdateItem(int index, int items)
{
	std::string sql = "Update tbItem SET ";
	switch (index)
	{
	case 1:
		sql.append("itembrick = " + std::to_string(items));
		break;
	case 2:
		sql.append("itemtool = " + std::to_string(items));
		break;
	case 3:
		sql.append("itemelectric = " + std::to_string(items));
		break;
	default:
		break;
	}
	sql.append(" where id = 1");

	DbContext::OpenConnect();
	sqlite3_exec(_dataBase, sql.c_str(), NULL, NULL, NULL);
	DbContext::CloseConnect();
}

int DbContext::GetScore()
{
	int _x;
	DbContext::OpenConnect();
	sqlite3_stmt* stmt = nullptr;

	sqlite3_prepare_v2(_dataBase, "SELECT * FROM tbScore", -1, &stmt, nullptr);

	while (true)
	{
		int result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			_x = sqlite3_column_int(stmt, 1);
		}
		else
		{
			break;
		}
	}
	DbContext::CloseConnect();
	return _x;
}

void DbContext::UpdateScore(int score)
{
	std::string sql1 = "Update tbScore SET ";
	sql1.append("score=" + std::to_string(score));
	sql1.append(" Where id = 1");
	DbContext::OpenConnect();
	sqlite3_exec(_dataBase, sql1.c_str(), NULL, NULL, NULL);
	DbContext::CloseConnect();
}

int DbContext::GetSound(int index)
{
	if (index < 1 || index > 2)
	{
		return 0;
	}
	int _x;
	DbContext::OpenConnect();
	sqlite3_stmt* stmt = nullptr;

	sqlite3_prepare_v2(_dataBase, "SELECT * FROM tbSound", -1, &stmt, nullptr);

	while (true)
	{
		int result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			_x = sqlite3_column_int(stmt, index);
		}
		else
		{
			break;
		}
	}
	DbContext::CloseConnect();
	return _x;
}

void DbContext::UpdateSound(int sf, int bg)
{
	std::string sql1 = "Update tbSound SET ";
	sql1.append("sound=" + std::to_string(sf));
	sql1.append(",bgm=" + std::to_string(bg));
	sql1.append(" Where id = 1");
	DbContext::OpenConnect();
	sqlite3_exec(_dataBase, sql1.c_str(), NULL, NULL, NULL);
	DbContext::CloseConnect();
}


