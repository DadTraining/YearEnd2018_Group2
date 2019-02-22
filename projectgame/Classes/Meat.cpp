#include"Meat.h"
#include"define.h"
#include "Constants.h"
#include "MyBodyParser.h"

Meat::Meat(cocos2d::Scene * scene) : Model()
{
	mSprite = cocos2d::Sprite::create(MEAT);
	
	SetVisible(false);
	scene->addChild(mSprite);
}

Meat::~Meat()
{

}

void Meat::Update()
{
	
}

void Meat::Init()
{
	
}
