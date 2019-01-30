#include "Shark.h"
#include "define.h"


Shark::Shark()
{
}

/*initialization shark*/
Shark::Shark(cocos2d::Scene * scene)
{
	mSprite = cocos2d::Sprite::create();
	//Init();	
	mStatus = " ";
	SetVisible(false);
	scene->addChild(mSprite, 1);
}

Shark::Shark(const Shark * shark)
{
}


Shark::~Shark()
{
}

void Shark::Damaged()
{
}

void Shark::Killed()
{
	mSprite->stopAllActions();
	mSprite->setFlippedY(true);
	mSprite->setPositionZ(-1);
	auto _sct = cocos2d::ScaleTo::create(1, 0);
	auto _move = cocos2d::MoveTo::create(2, cocos2d::Vec2(mSprite->getPosition().x, SCREEN_H));
	auto _fOut = cocos2d::FadeOut::create(2);
	auto _fIn = cocos2d::FadeIn::create(0.1);
	auto _spawn = cocos2d::Spawn::create(
		//_sct,
		_move,
		_fOut,
		nullptr
	);
	auto _vis = cocos2d::CallFunc::create([=]() {
		mSprite->setFlippedY(false);
		Model::SetSpriteVisible(false);
	});
	auto _sqe = cocos2d::Sequence::create(
		_spawn,
		_vis,
		_fIn,
		nullptr
	);
	mSprite->runAction(_sqe);
}

void Shark::Angry()
{
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
		if (_pos.x > SCREEN_W)
		{
			SetVisible(false);
			mStatus = " ";
			mSprite->stopAllActions();
		}

	}
	else
	{
		_pos.x -= mSpeed * SHARK_SPEED_RUNAWAY;
		if (_pos.x < 0)
		{
			SetVisible(false);
			mStatus = " ";
			mSprite->stopAllActions();
		}
	}
	mSprite->setPosition(_pos);
}

void Shark::ChangeDirection()
{
}

void Shark::Clone()
{
}

/*shark bite cable */
void Shark::BiteAnimation()
{
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
	mSprite->setPosition(mPos);
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
			&& _pos.x > SCREEN_W / 2 - mSpeed)
		{
			_pos.x -= mSpeed;
			mSprite->setPosition(_pos);
			if (_pos.x < SCREEN_W / 2)
			{
				Shark::BiteAnimation();
				//SetAlive(false);
				//Shark::Killed();

			}
		}
		else if (!mMoveToLeft
			&& _pos.x < SCREEN_W / 2 + mSpeed)
		{
			_pos.x += mSpeed;
			mSprite->setPosition(_pos);
			if (_pos.x > SCREEN_W / 2)
			{
				Shark::BiteAnimation();
				//SetAlive(false);
				//Shark::Killed();
			}
		}

	}
}

void Shark::RunAwayAnimation()
{
	mSprite->stopAllActions();
	auto _animate = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_RUN_AWAY_START, SHARK_RUN_AWAY_FRAME, mDelay - 0.05));
	auto _visi = cocos2d::CallFunc::create([=]() {
		mSprite->stopAllActions();
		//mMoveToLeft = !mMoveToLeft;
		mPos = mSprite->getPosition();
		mSprite->setFlipX(!mMoveToLeft);
		mStatus = SHARK_STATUS_RUNAWAY;
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
	auto _pos = mSprite->getPosition();
	if (mStatus == " " || mStatus.empty())
	{
		Shark::Move();
	}
	else if (mStatus == SHARK_STATUS_RUNAWAY)
	{
		Shark::RunAway();
	}

}

/*initialization for shark*/
void Shark::Init()
{
	SetVisible(true);
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
		mSize = SHARK_SIZE_SMALL;
		mDelay = SHARK_DELAY_SMALL;
		mSpeed = SHARK_SPEED_SMALL;
		break;
	case 2:
		mSize = SHARK_SIZE_NORMAL;
		mDelay = SHARK_DELAY_NORMAL;
		mSpeed = SHARK_SPEED_NORMAL;
		break;
	case 3:
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

	auto posY = cocos2d::random(SHARK_ZONE_UNDER, SCREEN_H - SHARK_ZONE_TOP);
	if (mMoveToLeft)
	{
		mPos = cocos2d::Vec2(SCREEN_W + SHARK_POS, posY);
		mSprite->setAnchorPoint(cocos2d::Vec2(0, 0.5));
	}
	else
	{
		mPos = cocos2d::Vec2(-SHARK_POS, posY);
		mSprite->setAnchorPoint(cocos2d::Vec2(1, 0.5));
	}
	mSprite->setFlipX(mMoveToLeft);
	Shark::SwimAnimation();

}
