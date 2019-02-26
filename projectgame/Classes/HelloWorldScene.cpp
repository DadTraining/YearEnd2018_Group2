#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MapScene.h"
#include "PopUpPlay.h"
#include "PopUpSetting.h"
#include "Popup.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

	PopupSetting *popup = PopupSetting::create();
	addChild(popup);



    return true;
}

