#include "TradesWoman.h"
TradesWoman::TradesWoman(void)
{
	Sprite::initWithSpriteFrameName("npc_2007.png");
}


TradesWoman::~TradesWoman(void)
{
}

void TradesWoman::action1()
{
	this->stopAllActions();


	SpriteFrameCache * cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame *> vec;

	char name[20];
	for (int i = 1;i<=11;i++)
	{
		if (i<10)
		{
			sprintf(name,"npc_100%d.png",i);
		}
		else
		{
			sprintf(name,"npc_10%d.png",i);
		}
		SpriteFrame * frame = cache->getSpriteFrameByName(name);
		vec.pushBack(frame);
	}
	auto plistAnimation = Animation::createWithSpriteFrames(vec,0.2f);
	auto animate = Animate::create(plistAnimation);
	auto seq = Sequence::create(animate,
								CCFlipX::create(true),
								CCFlipX::create(false),
								CCCallFunc::create(CC_CALLBACK_0(TradesWoman::action2,this)),
								NULL);
	this->runAction(seq);
}

void TradesWoman::action2()
{
	this->stopAllActions();


	SpriteFrameCache * cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame *> vec;

	char name[20];
	for (int i = 2;i<=10;i++)
	{
		if (i<10)
		{
			sprintf(name,"npc_200%d.png",i);
		}
		else
		{
			sprintf(name,"npc_20%d.png",i);
		}
		SpriteFrame * frame = cache->getSpriteFrameByName(name);
		vec.pushBack(frame);
	}
	auto plistAnimation = Animation::createWithSpriteFrames(vec,0.2f);
	auto animate = Animate::create(plistAnimation);
	auto seq = Sequence::create(animate,
								CCFlipX::create(true),
								CCFlipX::create(false),
								NULL);
	this->runAction(RepeatForever::create(seq));
}

void TradesWoman::action3()
{
	this->stopAllActions();


	SpriteFrameCache * cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame *> vec;

	char name[20];
	for (int i = 2;i<=10;i++)
	{
		if (i<10)
		{
			sprintf(name,"npc_300%d.png",i);
		}
		else
		{
			sprintf(name,"npc_30%d.png",i);
		}
		SpriteFrame * frame = cache->getSpriteFrameByName(name);
		vec.pushBack(frame);
	}
	auto plistAnimation = Animation::createWithSpriteFrames(vec,0.2f);
	auto animate = Animate::create(plistAnimation);
	auto seq = Sequence::create(animate,
		CCFlipX::create(true),
		CCFlipX::create(false),
		CCCallFunc::create(CC_CALLBACK_0(TradesWoman::action2,this)),
		NULL);
	this->runAction(seq);
}


