#pragma once
#include "cocos2d.h"
#include "Model.h"

using namespace cocos2d;
using namespace std;

class MapScene :public cocos2d::Scene
{ private:

  public:
	  /*MapScene(cocos2d::Scene *scene);
	  ~MapScene();*/
	 static cocos2d::Scene* createScene();
	  virtual bool init();
	  CREATE_FUNC(MapScene);
};