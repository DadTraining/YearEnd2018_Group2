#include"Item.h"
#include"cocos2d.h"
#include"Model.h"
#include "define.h"
#include "Constants.h"
#include "Cable.h"


Item::Item()
{
}

Item::Item(cocos2d::Scene * scene)
{ 
	mStatusStun = false;
	mTimeStun = 0;
}

Item::~Item()
{
}

void Item::Init()
{
}

void Item::Update()
{
	if (mStatusStun) {
		mTimeStun++;
		if (mTimeStun % 50==0)
		{
			mStatusStun = false;
			mTimeStun = 0;
			ChangeStatusStun();
		}
	}
}


void Item::Behavior()
{
}

void Item::OnClickMenuItem(cocos2d::Ref * sender)
{
}



void Item::IncreaseBlood()
{
}

void Item::StunShark(std::vector<Shark*> sharkList)
{
	mSharkList = sharkList;
	for (int i = 0; i < sharkList.size(); i++)
	{
			for (int j = 0; j < 8; j++)
			{
				sharkList[i]->UnUpdate(sharkList[i]->GetPosition());
			}
	}
	mStatusStun = true;
}

void Item::KillSharkByBoom(std::vector<Shark*> sharkList)
{
	for (int i = 0; i < sharkList.size(); i++)
	{
		if (sharkList[i]->IsAlive())
		{
			sharkList[i]->DamagedElectronic();
		}
	}
}

void Item::ChangeStatusStun()
{
	for (int i = 0; i < mSharkList.size(); i++)
	{
		mSharkList[i]->CallBackStatus();
	}
}






