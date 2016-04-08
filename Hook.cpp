#include "Hook.h"
#include "math.h"

Hook::Hook(void)
{
	Sprite::initWithFile("hook.png");
	isCatchItem = false;
	isBack = true;
}


Hook::~Hook(void)
{
}

void Hook::runRotate()
{
	
	this->setAnchorPoint(Vec2(0.5,1));
	
	auto action1 = RotateTo::create(2,-90);
	
	auto action2 = RotateTo::create(2,90);

	
	auto rotate = this->getRotation();

	Sequence * seq;

	if (rotate>0)
	{
		seq = Sequence::create(action1,action2,NULL);
	}
	else
	{
		seq = Sequence::create(action2,action1,NULL);
	}

	auto repeat = RepeatForever::create(seq);
	this->runAction(repeat);

	isBack = true;
}

void Hook::runToPoint(Point p)
{
	 this->stopAllActions();
	 Point start = this->getPosition();
	 float distance = sqrt(pow(start.x-p.x,2)+pow(start.y-p.y,2));
	 float time = distance*0.01;

	 auto move = MoveTo::create(time,p);
	 auto func = CallFunc::create(CC_CALLBACK_0(Hook::runBack,this));
	 auto seq = Sequence::create(move,func,NULL);
	 this->runAction(seq);
}

void Hook::runBack()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto action = MoveTo::create(2,Point(238,138));
	auto func = CallFunc::create(CC_CALLBACK_0(Hook::runRotate,this));
	auto seq = Sequence::create(action,func,NULL);

	this->runAction(seq);
}

void Hook::runTarget()
{
	float x,y;
	float rotate = this->getRotation();
	if (rotate>0)
	{
		if (rotate<=45)
		{
			y = 0.0;
			x = 240-160*tan(rotate*3.1415/180);
		}
		else
		{
			x = 0.0;
			y = 160 - 240/tan(rotate*3.1415/180);
		}
	}
	else if (rotate<0)
	{
		if (rotate<=-45)
		{
			x = 480;
			y = 160 + 240/tan(rotate*3.1415/180);
		}
		else
		{
			y = 0.0;
			x = 240 - 160*tan(rotate*3.1415/180);
		}
	}
	else
	{
		x = 238;
		y = 138;
	}

	this->runToPoint(Point(x,y));

	isBack = false;
}
