#include "Shark.h"
#include "define.h"
#include "Constants.h"
#include "MyBodyParser.h"
#include "Cable.h"


Shark::Shark()
{
}

/*initialization shark*/
Shark::Shark(cocos2d::Scene * scene)
{

	mSprite = cocos2d::Sprite::create("shark/shark.png");
	SetStatus(SHARK_STATUS_NORMAL);
	mOldStatus = SHARK_STATUS_NORMAL;
	SetVisible(false);
	scene->addChild(mSprite, 99);
	color_1st = cocos2d::Sprite::create(SHARK_COLOR_BLACK);
	color_2nd = cocos2d::Sprite::create(SHARK_COLOR_BLACK);
	Shark::setShowColorVisible();
	scene->addChild(color_1st, 101);
	scene->addChild(color_2nd, 101);

	AddStun(scene);
	//Init();
}

Shark::Shark(const Shark * shark)
{

}


Shark::~Shark()
{
	mSprite->release();

}


void Shark::DamagedElectronic()
{
	mSprite->stopAllActions();
	mStatus = SHARK_STATUS_DAMAGED_BY_ELECTRONIC;
	auto animate = cocos2d::Animate::create(Model::CreateAnimation(SHARK_BE_DAMAGE_BY_ELECTRONIC, 1, 3, 0.075));
	auto callback = cocos2d::CallFunc::create([=]() {
		mStatus = mOldStatus;
		Shark::Killed();
	});

	auto seq = cocos2d::Sequence::create(
		cocos2d::Repeat::create(animate, 3),
		callback,
		nullptr
	);
	mSprite->runAction(seq);
}

void Shark::StunAnimation()
{
	if (Model::SpriteIsVisible())
	{
		Shark::SetStun(true);
		if (mMoveToLeft)
		{
			mStunSprite->setAnchorPoint(cocos2d::Vec2(1, 0.2));
		}
		else
		{
			mStunSprite->setAnchorPoint(cocos2d::Vec2(0, 0.2));
		}
		mStunSprite->setPosition(this->GetLocation());
		auto animate = cocos2d::Animate::create(Model::CreateAnimation(SHARK_STATUS_STUN, 1, 4, 0.15));
		auto callback = cocos2d::CallFunc::create([=]() {
			Shark::SetStun(false);
		});

		auto seq = cocos2d::Sequence::create(
			cocos2d::Repeat::create(animate, 2),
			callback,
			nullptr
		);
		mStunSprite->runAction(seq);
	}
}

void Shark::Killed()
{
	auto score = InfoMap::getScore();
	InfoMap::setScore(score + this->mScore);
	mSprite->stopAllActions();
	mSprite->setFlippedY(true);
	mSprite->setPositionZ(-1);
	SetAlive(false);
	Shark::setShowColorVisible();
	auto _sct = cocos2d::ScaleTo::create(1, 0);
	auto _move = cocos2d::MoveTo::create(2, cocos2d::Vec2(mSprite->getPosition().x, SCREEN_H));
	auto _fOut = cocos2d::FadeOut::create(2);
	auto _fIn = cocos2d::FadeIn::create(0.1);
	auto _spawn = cocos2d::Spawn::create(
		_move,
		//_fOut,
		nullptr
	);
	auto _vis = cocos2d::CallFunc::create([=]() {
		//mSprite->setFlippedY(false);
		Model::SetSpriteVisible(false);
	});
	auto _sqe = cocos2d::Sequence::create(
		_spawn,
		_vis,
		//_fIn,
		nullptr
	);
	mSprite->runAction(_sqe);
}

void Shark::Angry()
{
	if (mStatus == SHARK_STATUS_NORMAL)
	{
		auto location = Shark::GetLocation().x;
		if (Shark::GetDirection() && location - mSpeed * 13 > Constants::getVisibleSize().width / 2)
		{
			mSpeed *= 10;
			mStatus = SHARK_STATUS_ANGRY;
		}
		else if (!Shark::GetDirection() && location + mSpeed * 13 < Constants::getVisibleSize().width / 2)
		{
			mSpeed *= 10;
			mStatus = SHARK_STATUS_ANGRY;
		}
	}
}

void Shark::Normal()
{
}


void Shark::RunAway()
{

	auto _pos = mSprite->getPosition();
	if (mMoveToLeft)
	{
		_pos.x += mSpeed * SHARK_SPEED_RUNAWAY;
		if (_pos.x > Constants::getVisibleSize().width)
		{
			SetVisible(false);
			mStatus = SHARK_STATUS_NORMAL;
			mOldStatus = SHARK_STATUS_NORMAL;
			mSprite->stopAllActions();
		}

	}
	else
	{
		_pos.x -= mSpeed * SHARK_SPEED_RUNAWAY;
		if (_pos.x < 0)
		{
			SetVisible(false);
			mStatus = SHARK_STATUS_NORMAL;
			mOldStatus = SHARK_STATUS_NORMAL;
			mSprite->stopAllActions();
		}
	}
	mSprite->setPosition(_pos);
}

void Shark::ChangeDirection()
{
}

void Shark::Clone(Shark * shark)
{
	mSprite->stopAllActions();
	this->mSize = shark->GetMSize();
	this->mColor = shark->GetColor();
	this->mDelay = shark->GetDelay();
	Shark::SwimAnimation();
	SetVisible(true);
	this->mIsBitten = shark->IsBitten();
	this->mStatus = shark->GetStatus();
	this->mOldStatus = shark->GetOldStatus();
	this->mSpeed = shark->GetSpeed();
	this->mTotalColor = shark->GetTotalColor();
	this->mScore = shark->GetScore();
	this->mMoveToLeft = shark->GetDirection();
	mSprite->setFlipX(mMoveToLeft);
	this->mPos = shark->GetPosition();
	auto _x = mSprite->getContentSize().width;
	if (mMoveToLeft)
	{
		mPos.x += _x;
	}
	else
	{
		mPos.x -= _x;
	}
	mSprite->setPosition(mPos);

}



/*shark bite cable */
void Shark::BiteAnimation()
{
	SetStatus(SHARK_STATUS_BITE);
	//this->SetAlive(true);
	mSpeed = 1.5;
	mSprite->stopAllActions();
	auto _animate = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_BITE_START, SHARK_BITE_FRAME, mDelay));
	auto _visi = cocos2d::CallFunc::create([=]() {
		//SetVisible(false);
		//mSprite->stopAllActions();
		Shark::RunAwayAnimation();
	});


	auto sqe = cocos2d::Sequence::create(
		cocos2d::Repeat::create(_animate, 2),
		//cocos2d::DelayTime::create(0.5f),
		_visi,
		nullptr);
	mSprite->runAction(sqe);
}

//////////////////////////////////
/* this is animation of shark*/
void Shark::SwimAnimation()
{
	mSprite->setScale(mSize);
	auto ani = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_SWIM_START, SHARK_SWIM_FRAMES, mDelay));
	auto sqe = cocos2d::RepeatForever::create(ani);
	mSprite->runAction(sqe);
}

/* this is moving function of shark*/
void Shark::Move()
{
	if (mVisible)
	{
		auto _pos = mSprite->getPosition();
		if (mMoveToLeft
			&& _pos.x > Constants::getVisibleSize().width / 2 - mSpeed)
		{
			_pos.x -= mSpeed;
			mSprite->setPosition(_pos);

		}
		else if (!mMoveToLeft
			&& _pos.x < Constants::getVisibleSize().width / 2 + mSpeed)
		{
			_pos.x += mSpeed;
			mSprite->setPosition(_pos);
			if (_pos.x > Constants::getVisibleSize().width / 2)
			{
				Shark::BiteAnimation();
				//SetAlive(false);
				//Shark::Killed();
			}
		}

	}
}

void Shark::UnMove(cocos2d::Vec2 pos)
{
	if (mVisible)
	{
		mSprite->stopAllActions();
		mSprite->setPosition(pos);
	}

}

void Shark::RunAwayAnimation()
{
	mSprite->stopAllActions();
	//CCLOG("%s", mStatus);
	Shark::SetAlive(false);
	mStatus = SHARK_STATUS_RUNAWAY_ANIMATION;
	auto _animate = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_RUN_AWAY_START, SHARK_RUN_AWAY_FRAME, mDelay - 0.05));
	auto _visi = cocos2d::CallFunc::create([=]() {
		mSprite->stopAllActions();
		//mMoveToLeft = !mMoveToLeft;
		mPos = mSprite->getPosition();
		mSprite->setFlipX(!mMoveToLeft);
		mStatus = SHARK_STATUS_RUNAWAY;
		mOldStatus = SHARK_STATUS_RUNAWAY;
		Shark::SwimAnimation();
	});
	auto _run = cocos2d::CallFunc::create([=]() {

	});
	auto sqe = cocos2d::Sequence::create(
		_animate,
		_visi,
		_run,
		nullptr);
	mSprite->runAction(sqe);
}

/*update per frame*/
void Shark::Update()
{
	//auto _pos = mSprite->getPosition();
	if (mStatus == SHARK_STATUS_NORMAL || mStatus.empty() || mStatus == SHARK_STATUS_ANGRY)
	{
		Shark::Move();
	}
	else if (mStatus == SHARK_STATUS_RUNAWAY)
	{
		Shark::RunAway();
		//Cable::Bitten();
	}
	else if (mStatus == SHARK_STATUS_STUN)
	{

	}

	if (mTotalColor != 1)
	{
		SetPositionCheckColor();
	}

}

void Shark::UnUpdate(cocos2d::Vec2 pos)
{
	this->mStatus = SHARK_STATUS_STUN;
	Shark::StunAnimation();
}

/*initialization for shark*/
void Shark::Init()
{
	mSprite->setFlipY(false);
	mSprite->runAction(
		cocos2d::FadeIn::create(0.1)
	);
	mSprite->stopAllActions();
	mStatus = SHARK_STATUS_NORMAL;
	mOldStatus = SHARK_STATUS_NORMAL;
	SetVisible(true);


	setIsBitten(true);
	//set color
	if (mTotalColor == 1)
	{
		SharkSingleSkin();
	}
	else
	{
		SharkMultiSkin();
		Shark::setShowColorVisible();
	}
	//set size
	int size = cocos2d::random(1, 3);
	switch (size)
	{
	case 1:
		mScore = 10;
		mSize = SHARK_SIZE_SMALL;
		mDelay = SHARK_DELAY_SMALL;
		mSpeed = SHARK_SPEED_SMALL;
		break;
	case 2:
		mScore = 20;
		mSize = SHARK_SIZE_NORMAL;
		mDelay = SHARK_DELAY_NORMAL;
		mSpeed = SHARK_SPEED_NORMAL;
		break;
	case 3:
		mScore = 30;
		mSize = SHARK_SIZE_BIG;
		mDelay = SHARK_DELAY_BIG;
		mSpeed = SHARK_SPEED_BIG;
		break;
	default:
		mSize = SHARK_SIZE_NORMAL;
		mDelay = SHARK_DELAY_NORMAL;
		mSpeed = SHARK_SPEED_NORMAL;
		break;
	}

	//set position
	auto posX = cocos2d::random(1, 2);
	if (posX == 1)
	{
		mMoveToLeft = true; // run from right to left
	}
	else
	{
		mMoveToLeft = false; // run from left to right
	}

	auto posY = cocos2d::random(Constants::getVisibleSize().height * 4 / 10, Constants::getVisibleSize().height - SHARK_ZONE_TOP);
	Shark::SwimAnimation();
	auto sharkSize = mSprite->getContentSize().width / 2;
	if (mMoveToLeft)
	{
		mPos = cocos2d::Vec2(Constants::getVisibleSize().width + sharkSize, posY);
	}
	else
	{
		mPos = cocos2d::Vec2(-sharkSize, posY);
	}
	mSprite->setPosition(mPos);
	mSprite->setFlipX(mMoveToLeft);

	SetPhysicsBody();

}

void Shark::SetStatus(std::string status)
{
	this->mStatus = status;
	this->mOldStatus = status;
}

std::string Shark::GetColor()
{
	return mColor;
}

bool Shark::GetDirection()
{
	return mMoveToLeft;

}

std::string Shark::GetStatus()
{
	return mStatus;

}

std::string Shark::GetOldStatus()
{
	return mOldStatus;
}

float Shark::GetDelay()
{
	return mDelay;

}

float Shark::GetMSize()
{
	return mSize;
}

float Shark::GetSpeed()
{
	return mSpeed;
}

int Shark::GetTotalColor()
{
	return mTotalColor;
}

int Shark::GetScore()
{
	return mScore;
}

void Shark::SetStun(bool vis)
{
	mStunSprite->setVisible(vis);
}

void Shark::AddStun(cocos2d::Scene* scene)
{
	mStunSprite = cocos2d::Sprite::create();
	Shark::SetStun(false);
	scene->addChild(mStunSprite, 101);
}

void Shark::SetPhysicsBody()
{
	cocos2d::PhysicsBody* spriteBody;
	if (mMoveToLeft)
	{
		spriteBody = MyBodyParser::getInstance()->bodyFormJson(mSprite, SHARK_BODY_SPRITE_LEFT, cocos2d::PhysicsMaterial(1, 1, 0));
	}
	else
	{
		spriteBody = MyBodyParser::getInstance()->bodyFormJson(mSprite, SHARK_BODY_SPRITE_RIGHT, cocos2d::PhysicsMaterial(1, 1, 0));
	}
	if (spriteBody != nullptr)
	{
		spriteBody->setDynamic(false);
		mSprite->setPhysicsBody(spriteBody);
		mSprite->getPhysicsBody()->setCollisionBitmask(0x02);
		mSprite->getPhysicsBody()->setContactTestBitmask(true);
	}
}

void Shark::SharkSingleSkin()
{
	int color = cocos2d::random(1, 3);
	switch (color)
	{
	case 1:
		mColor = SHARK_BLUE;
		break;
	case 2:
		mColor = SHARK_RED;
		break;
	case 3:
		mColor = SHARK_YELLOW;
		break;
	}

}

void Shark::SetNumSkinForShark(int num)
{
	mTotalColor = num;
}

void Shark::SharkMultiSkin()
{
	mTotalColor = 2;
	mTotalDuplicate = 0;
	int color = cocos2d::random(1, 3);
	switch (color)
	{
	case 1:
		mColor = SHARK_ORANGE;
		mColor_1st = SHARK_YELLOW;
		mColor_2nd = SHARK_RED;
		break;
	case 2:
		mColor = SHARK_GREEN;
		mColor_1st = SHARK_YELLOW;
		mColor_2nd = SHARK_BLUE;
		break;
	case 3:
		mColor = SHARK_PURPLE;
		mColor_1st = SHARK_BLUE;
		mColor_2nd = SHARK_RED;
		break;
	}
	color_1st->setSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("black.png"));
	color_2nd->setSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("black.png"));

}

bool Shark::CheckColor(std::string color)
{
	if (mTotalColor == 1)
	{
		return mColor == color;
	}
	else
	{
		if (mColor_1st == color || mColor_2nd == color)
		{
			std::string _name;

			if (color == SHARK_YELLOW)
			{
				_name = "yellow.png";
			}
			else if (color == SHARK_BLUE)
			{
				_name = "blue.png";
			}
			else if (color == SHARK_RED)
			{
				_name = "red.png";
			}

			if (mTotalDuplicate == 0)
			{
				color_1st->setSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(_name));
				mTotalDuplicate += 1;
			}
			else
			{
				color_2nd->setSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(_name));
				mTotalDuplicate += 1;
			}
			return true;
		}
		return false;
	}
}

void Shark::SetPositionCheckColor()
{
	color_1st->setPosition(
		Shark::GetLocation().x,
		Shark::GetLocation().y - Shark::GetSprite()->getContentSize().height / 2 - 3
	);
	if (mMoveToLeft)
	{
		color_2nd->setPosition(
			color_1st->getPosition().x - color_1st->getContentSize().width,
			color_1st->getPosition().y
		);
	}
	else
	{
		color_2nd->setPosition(
			color_1st->getPosition().x + color_1st->getContentSize().width,
			color_1st->getPosition().y
		);
	}
}

bool Shark::EnoughColor()
{
	if (this->mTotalDuplicate == 2)
	{
		return true;
	}
	return false;
}

void Shark::setShowColorVisible()
{
	color_1st->setVisible(this->IsVisible());
	color_2nd->setVisible(this->IsVisible());
}





void Shark::CallBackStatus()
{
	mStatus = mOldStatus;
}

bool Shark::IsBitten()
{
	return mIsBitten;
}

void Shark::setIsBitten(bool bitten)
{
	mIsBitten = bitten;
}


