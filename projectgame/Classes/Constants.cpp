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
bool Constants::onBGM = true;
bool Constants::onSFX = true;
std::string Constants::nameShip = "ship/Ship.png";
std::vector<SkinGame*> Constants::listSkin;

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
	if (index < 16)
	{
		auto map = listMap.at(index);
		InfoMap::setSharPhases(
			map->GetPhase(1),
			map->GetPhase(2),
			map->GetPhase(3),
			map->GetSharksSkin(),
			map->get3Star(),
			map->get2Star()
		);
		InfoMap::setMapLevel(index);
	}
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
	if (!map->WasPlay())
	{
		map->SetStar(star);
		map->setPlayPass(pass);
		map->SetScore(score);
	}
	else
	{
		if (pass)
		{
			if (map->GetStar() < star)
			{
				map->SetStar(star);
			}
			if (map->GetScore() < score)
			{
				map->SetScore(score);
			}
		}
	}
	if (pass)
	{
		if (lv < 16 && (lv == 4 || lv == 8 || lv == 12))
		{
			if (Constants::GetTotalStar() == 12 && lv == 4)
			{
				listMap.at(lv)->AllowPlay();
			}
			else if (Constants::GetTotalStar() == 24 && lv == 8)
			{
				listMap.at(lv)->AllowPlay();
			}
			else if (Constants::GetTotalStar() == 36 && lv == 12)
			{
				listMap.at(lv)->AllowPlay();
			}
		}
		else
		{
			if (lv <16)
			{
				listMap.at(lv)->AllowPlay();
			}
		}

		DbContext::UpdateDataMap(lv, map->GetStar(), map->GetScore());
		DbContext::UpdateScore(Constants::GetTotalCoin() + score);
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
	if (Constants::GetTotalCoin() >= COST_BUY_BOOM)
	{
		boom += 1;
		DbContext::UpdateItem(3, boom);
		Constants::SetTotalCoin(totalCoin - COST_BUY_BOOM);
		DbContext::UpdateScore(totalCoin);

		return true;
	}
	return false;
}

bool Constants::BuyBricks()
{
	if (Constants::GetTotalCoin() >= COST_BUY_BRICK)
	{
		brick += 1;
		DbContext::UpdateItem(1, brick);
		Constants::SetTotalCoin(totalCoin - COST_BUY_BRICK);
		DbContext::UpdateScore(totalCoin);
		return true;
	}
	return false;

}

bool Constants::BuyHps()
{
	if (Constants::GetTotalCoin() >= COST_BUY_HP)
	{
		hp += 1;
		Constants::SetTotalCoin(totalCoin - COST_BUY_HP);
		DbContext::UpdateItem(2, hp);
		DbContext::UpdateScore(totalCoin);

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
	totalCoin = DbContext::GetScore();
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

bool Constants::AllowPlayNext(int lv)
{
	if (lv <16)
	{
		return listMap.at(lv)->isAllowPlay();
	}
	return false;
}

void Constants::setOnBGM(bool on)
{
	onBGM = on;
}

void Constants::changeOnBGM()
{
	onBGM = !onBGM;
	DbContext::UpdateSound(onSFX ? 1 : 0, onBGM ? 1 : 0);
}

bool Constants::getOnBGM()
{
	return onBGM;
}

void Constants::setOnSFX(bool on)
{
	onSFX = on;
}

void Constants::changeOnSFX()
{
	onSFX = !onSFX;
	DbContext::UpdateSound(onSFX ? 1 : 0, onBGM ? 1 : 0);
}

bool Constants::getOnSFX()
{
	return onSFX;
}

void Constants::SetSelectedShip(int id)
{
	for (int i = 0; i < listButton.size(); i++)
	{
		if (i != id)
		{
			listButton.at(i)->setEnabled(true);
		}
		else
		{
			listButton.at(i)->setEnabled(false);
		}
		listSkin.at(i)->SetIssue(false);
	}

	//listSkin = DbContext::GetListShip();
	//Constants::nameShip = listSkin.at(id + 1)->GetSkinText();
	listSkin.at(id)->SetIssue(true);
	DbContext::UpdateSkinShip(id + 1);
}

std::string Constants::GetNameShip()
{
	//std::string name;
	for (int i = 0; i < listSkin.size(); i++)
	{
		if (listSkin.at(i)->IsAllowUse())
		{
			return listSkin.at(i)->GetSkinText();
		}
	}

	return nullptr;
}

void Constants::LoadSkinGame()
{
	listSkin = DbContext::GetListShip();
}

void Constants::ReLoadShop()
{
	for (int i = 0; i < listSkin.size(); i++)
	{
		listButton.at(i)->setEnabled(!listSkin.at(i)->IsIssue());
	}
}


