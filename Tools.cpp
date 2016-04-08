#include "Tools.h"


//碰撞检测
bool Tools::isCollsion(Sprite * sp1,Sprite * sp2)
{
	Point p1 = sp1->getPosition();
	Point p2 = sp2->getPosition();

	auto size1 = sp1->getContentSize();
	auto size2 = sp2->getContentSize();

	if (abs(p1.x-p2.x)<= (size1.width+size2.width)/4 && abs(p1.y-p2.y)<=(size1.height+size2.height)/4)
	{
		return true;
	}
	return false;
}
//随机物品位置的函数
Point Tools::getPointWithType(ItemQuaulityType spriteType,ItemSizeType spriteSize)
{
	Point p;
	int x,y;
	x=rand();
	y=rand();
	switch (spriteType)
	{
	case Item_diamond:
	case Item_secret:
		{
			x = x%480;
			y = y%80;
		}
		break;
	case Item_gold:
		{
			switch (spriteSize)
			{
			case Item_small:
			case Item_middle:
				{
					x = x%480;
					y = y%120;
				}
				break;
			case Item_large:
				{
					x = x%480;
					y = y%80;
				}
				break;
			default:
				break;
			}
		}
	case Item_stone:
		{
			x = x%480;
			y = y%120;
		}
		break;
	default:
		break;
	}
	p.x = x;
	p.y = y;
	return p;
}
