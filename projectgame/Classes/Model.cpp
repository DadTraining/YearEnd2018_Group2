#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

/*set this visible shark alive
set sprite visible*/
void Model::SetVisible(bool vis)
{
	SetAlive(vis);
	SetSpriteVisible(vis);
}
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

/*get visible share
*true is alive
*false is death*/
bool Model::IsVisible()
{
	return mVisible;
}

cocos2d::Vec2 Model::GetPosition()
/*set Shark alive or death*/
void Model::SetAlive(bool vis)
{
	mVisible = vis;
}

/*set visible shark*/
void Model::SetSpriteVisible(bool vis)
{
	return this->GetSprite()->getPosition();
	mSprite->setVisible(vis);
}

/*return sprite is visible*/
bool Model::SpriteIsVisible()
{
	return mSprite->isVisible();
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
cocos2d::Vec2 Model::GetLocation() {
	return mSprite->getPosition();
cocos2d::Animation* Model::CreateAnimation(std::string name,int start, int frames, float delay)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> _frames;

	for (int i = start; i <= start+frames-1; i++)
	{
		char temp[20] = { 0 };
		sprintf(temp, "%d.png", i);
		std::string _name = name + temp;
		auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(_name);
		_frames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(_frames,delay);
	return animation;
}
