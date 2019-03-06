#include "Constants.h"
#include "define.h"
#include "DbContext.h"

cocos2d::Vector<cocos2d::ui::Button*> Constants::listButton;
std::vector<MapLevel*> Constants::listMap;
bool Constants::inMap;
int Constants::brick;
int Constants::hp;
int Constants::boom;
int Constants::totalCoin;
int Constants::totalStar;
bool Constants::pause;

cocos2d::Size Constants::getVisibleSize()
{
	return cocos2d::Director::getInstance()->getVisibleSize();
}



float Constants::setScaleSprite(float whichSize, float expectSize, float realSize)
{
	return (whichSize / expectSize) / realSize;
}

void Constants::AddButtonIntoMapLevel(cocos2d::ui::Button * btn)
{
	listButton.pushBack(btn);
}

void Constants::SetEnableTouchEvent(int index, bool enable)
{
	listButton.at(index)->setTouchEnabled(enable);
	listButton.at(index)->setBright(enable);
	listButton.at(index)->setEnabled(enable);
}

void Constants::SetEnableAllTouchEventOnMapLevel(bool enable)
{
	for (int i = 0; i < listButton.size(); i++)
	{
		listButton.at(i)->setTouchEnabled(enable);
	}
}

std::vector<MapLevel*> Constants::GetListMap()
{
	return listMap;
}

void Constants::AddMapIntoList(MapLevel * map)
{
	listMap.push_back(map);
}



void Constants::SetPhase(int index)
{
	auto map = listMap.at(index);
	InfoMap::setSharPhases(
		map->GetPhase(1),
		map->GetPhase(2),
		map->GetPhase(3),
		map->GetSharksSkin()
	);
	InfoMap::setMapLevel(index);
}

void Constants::ReleaseButton()
{
	listButton.clear();
}

bool Constants::ListButtonIsEmpty()
{
	return listButton.empty();
}

void Constants::EndGame(int lv, int star, bool pass, int score)
{
	auto map = listMap.at(lv - 1);
	map->SetStar(star);
	map->setPlayPass(pass);
	map->SetScore(score);
	if (pass)
	{
		if (lv < 16)
		{
			listMap.at(lv)->AllowPlay();
		}
		DbContext::UpdateDataMap(lv, star, score);
	}
	DbContext::UpdateItem(1, Constants::GetBricks());
	DbContext::UpdateItem(2, Constants::GetHps());
	DbContext::UpdateItem(3, Constants::GetBooms());
}

void Constants::setInMap(bool in)
{
	inMap = in;
}

bool Constants::isInMap()
{
	return inMap;
}

bool Constants::BuyBooms()
{
	if (Constants::GetTotalCoin() > COST_BUY_BOOM)
	{
		boom += 1;
		return true;
	}
	return false;
}

bool Constants::BuyBreacks()
{
	if (Constants::GetTotalCoin() > COST_BUY_BREACK)
	{
		brick += 3;
		return true;
	}
	return false;

}

bool Constants::BuyHps()
{
	if (Constants::GetTotalCoin() > COST_BUY_HP)
	{
		hp += 3;
		return true;
	}
	return false;
}

int Constants::GetBooms()
{
	return boom;
}

int Constants::GetHps()
{
	return hp;
}

int Constants::GetBricks()
{
	return brick;
}

void Constants::SetBooms(int num)
{
	boom = num;
}

void Constants::SetHps(int num)
{
	hp = num;
}

void Constants::SetBricks(int num)
{
	brick = num;
}

void Constants::RefreshItem()
{
	brick = DbContext::GetItem(1);
	hp = DbContext::GetItem(2);
	boom = DbContext::GetItem(3);
}

void Constants::SetTotalCoin(int coins)
{
	totalCoin = coins;
}

int Constants::GetTotalCoin()
{
	totalCoin = 0;
	for (int i = 0; i < listMap.size(); i++)
	{
		totalCoin += listMap.at(i)->GetScore();
	}
	return totalCoin;
}

int Constants::GetTotalStar()
{
	totalStar = 0;
	for (int i = 0; i < listMap.size(); i++)
	{
		totalStar += listMap.at(i)->GetStar();
	}
	return totalStar;
}

void Constants::SetTotalStar(int star)
{
	totalStar = star;
}




