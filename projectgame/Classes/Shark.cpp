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
	SetStatus(" ");
	mOldStatus = " ";
	SetVisible(false);
	scene->addChild(mSprite,99);
	//Init();
}

Shark::Shark(const Shark * shark)
{
	
}


Shark::~Shark()
{
	mSprite->release();

}

void Shark::Damaged()
{
}

void Shark::Killed()
{
	auto score = InfoMap::getScore();
	InfoMap::setScore(score + this->mScore);
	mSprite->stopAllActions();
	mSprite->setFlippedY(true);
	mSprite->setPositionZ(-1);
	SetAlive(false);
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
	if (mStatus != SHARK_STATUS_ANGRY )
	{
		if (mStatus != SHARK_STATUS_BITE)
		{
			mSpeed *= 5;
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
		if (_pos.x > Constants::getVisibleSize().width )
		{
			SetVisible(false);
			mStatus = " ";
			mOldStatus = " ";
			mSprite->stopAllActions();
		}

	}
	else
	{
		_pos.x -= mSpeed * SHARK_SPEED_RUNAWAY;
		if (_pos.x < 0)
		{
			SetVisible(false);
			mStatus = " "; mOldStatus = " ";
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
	if (mStatus == " " || mStatus.empty()|| mStatus == SHARK_STATUS_ANGRY)
	{
		Shark::Move();
		
	}
	else if (mStatus == SHARK_STATUS_RUNAWAY)
	{
		Shark::RunAway();
		//Cable::Bitten();
	}
	else if(mStatus == SHARK_STATUS_BITE)
	{

	}

}

void Shark::UnUpdate(cocos2d::Vec2 pos)
{
	this->mStatus = SHARK_STATUS_STUN;
}

/*initialization for shark*/
void Shark::Init()
{
	mSprite->setFlipY(false);
	mSprite->runAction(
		cocos2d::FadeIn::create(0.1)
	);
	mSprite->stopAllActions();
	mStatus = " ";
	mOldStatus = " ";
	SetVisible(true);
	setIsBitten(true);
	//set color
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

	auto posY = cocos2d::random(Constants::getVisibleSize().height*4/10, Constants::getVisibleSize().height - SHARK_ZONE_TOP);
	Shark::SwimAnimation();
	auto sharkSize = mSprite->getContentSize().width / 2;
	if (mMoveToLeft)
	{
		mPos = cocos2d::Vec2(Constants::getVisibleSize().width  + sharkSize, posY);
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

void Shark::SetOldStatus()
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


