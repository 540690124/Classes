#include "Miner.h"


Miner::Miner(void)
{
	Sprite::initWithFile("miner.png");
}


Miner::~Miner(void)
{
}

void Miner::runMinerAction(DirectionType direction)
{
	this->stopAllActions();

	auto cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame *> vec;
	char name[20];
	switch (direction)
	{
	case right:
		for (int i = 1;i <= 5;i++)
		{
			sprintf(name,"miner_070%d.png",i);
			auto frame = cache->getSpriteFrameByName(name);
			vec.pushBack(frame);
		}
		break;
	case left:
		for (int i = 6;i <= 10;i++)
		{
			if (i<10)
			{
				sprintf(name,"miner_070%d.png",i);
			}
			else if (i = 10)
			{
				sprintf(name,"miner_07%d.png",i);
			}
			auto frame = cache->getSpriteFrameByName(name);
			vec.pushBack(frame);
		}
		break;
	default:
		break;
	}

	auto animation = Animation::createWithSpriteFrames(vec,0.2f);
	auto animate = Animate::create(animation);
	auto seq = Sequence::create(animate,CCFlipX::create(true),CCFlipX::create(false),NULL);
	auto repeat = RepeatForever::create(seq);

	this->runAction(repeat);
}
