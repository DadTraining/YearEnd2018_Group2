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
}

void Shark::Angry()
{
}

void Shark::Normal()
{
}


void Shark::RunAway()
{
	
}

void Shark::ChangeDirection()
{
}

void Shark::Clone()
{
}

/*shark bite cable */
void Shark::Bite()
{
	mSprite->stopAllActions();
	auto animate = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_BITE_START, SHARK_BITE_FRAME, mDelay));
	auto visi = cocos2d::CallFunc::create([=]() {
		SetVisible(false);
		mSprite->stopAllActions();
	});
	auto sqe = cocos2d::Sequence::create(
		cocos2d::Repeat::create(animate, 2),
		//cocos2d::DelayTime::create(0.5f),
		visi,
		nullptr);
	mSprite->runAction(sqe);
}

void Shark::Swim()
{
	mSprite->setPosition(mPos);
	mSprite->setScale(mSize);
	auto ani = cocos2d::Animate::create(CreateAnimation(mColor, SHARK_SWIM_START, SHARK_SWIM_FRAMES, mDelay));
	auto sqe = cocos2d::RepeatForever::create(ani);
	mSprite->runAction(sqe);
}

/*update per frame*/
void Shark::Update()
{
	if (mVisible)
	{
		auto _pos = mSprite->getPosition();
		if (mPosLeft && _pos.x > SCREEN_W / 2 - mSpeed)
		{
			_pos.x -= mSpeed;
			mSprite->setPosition(_pos);
			if (_pos.x < SCREEN_W / 2)
			{
				Shark::Bite();
				//mVisible = false;
			}
		}
		else if (!mPosLeft && _pos.x < SCREEN_W / 2 + mSpeed)
		{
			_pos.x += mSpeed;
			mSprite->setPosition(_pos);
			if (_pos.x > SCREEN_W / 2)
			{
				Shark::Bite();
				//mVisible = false;
			}
		}
	}
}

/*initialization for shark*/
void Shark::Init()
{
	SetVisible(true);
	//set color
	int color = cocos2d::random(1, 6);
	switch (color)
	{
	case 1:
		mColor = SHARK_BLUE;
		break;
	case 2:
		mColor = SHARK_GREEN;
		break;
	case 3:
		mColor = SHARK_ORANGE;
		break;
	case 4:
		mColor = SHARK_PURPLE;
		break;
	case 5:
		mColor = SHARK_RED;
		break;
	case 6:
		mColor = SHARK_YELLOW;
		break;
	default:
		mColor = SHARK_BLUE;
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
		mPosLeft = true; // run right to left
	}
	else
	{
		mPosLeft = false; // run left to right
	}

	auto posY = cocos2d::random(100, SCREEN_H - 100);
	if (mPosLeft)
	{
		mPos = cocos2d::Vec2(SCREEN_W + SHARK_POS, posY);
		mSprite->setAnchorPoint(cocos2d::Vec2(0, 0.5));
	}
	else
	{
		mPos = cocos2d::Vec2(-SHARK_POS, posY);
		mSprite->setAnchorPoint(cocos2d::Vec2(1, 0.5));
	}
	mSprite->setFlipX(mPosLeft);
	Shark::Swim();

}
