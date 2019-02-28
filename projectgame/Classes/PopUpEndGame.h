#pragma once
#include "cocos2d.h"
#include "Popup.h"
#include "MapLevel.h"


class PopupEndGame : public Popup
{
private:
	
public:

    virtual bool init() override;
	virtual void onExit() override;
    
	
	void setLevel(int numLevel, int numStars);
	virtual void HandlTouch() override;
    CREATE_FUNC(PopupEndGame);
};

