#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::SetVisible(bool vis)
{
	mSprite->setVisible(vis);
	mVisible = vis;
}

bool Model::IsVisible()
{
	return mVisible;
}


cocos2d::Vec2 Model::GetPosition()
{
	return this->GetSprite()->getPosition();
}

void Model::SetPosition(cocos2d::Vec2 mPos)
{
	this->GetSprite()->setPosition(mPos);
}
cocos2d::Sprite * Model::GetSprite()
{
	return this->mSprite;
}

void Model::SetSprite(cocos2d::Sprite * sprite)
{
	this->mSprite = sprite;
}