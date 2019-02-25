#include "Constants.h"

cocos2d::Vector<cocos2d::ui::Button*> Constants::listButton;

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

void Constants::SetEnableTouchEvent(bool enable)
{
	for (int i = 0; i < listButton.size(); i++)
	{
		listButton.at(i)->setTouchEnabled(enable);
	}
}

