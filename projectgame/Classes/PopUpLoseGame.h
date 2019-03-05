#pragma once
#include "cocos2d.h"
#include "Popup.h"
#include "MapLevel.h"


class PopupLoseGame : public Popup
{
private:
	
public:

    virtual bool init() override;
	virtual void onExit() override;
    
	
	
	virtual void HandlTouch() override;
    CREATE_FUNC(PopupLoseGame);
};

