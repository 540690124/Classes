#pragma once
#include "cocos2d.h"
#include "ItemUnits.h"
USING_NS_CC;
class Tools
{
public:
	static bool isCollsion(Sprite * sp1,Sprite * sp2);
	static Point getPointWithType(ItemQuaulityType spriteType,ItemSizeType spriteSize);
};

