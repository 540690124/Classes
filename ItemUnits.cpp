#include "ItemUnits.h"

ItemUnits::~ItemUnits(void)
{
}

ItemUnits::ItemUnits(ItemQuaulityType spriteType,ItemSizeType spriteSize)
{
	isCatch = false;

	switch (spriteType)
	{
	case Item_stone:
		{
			switch (spriteSize)
			{
			case Item_small:
				{
					this->initWithFile("stone_small.png");
					score = 10;
					weight = 10;
				}
				break;
			case Item_middle:
				{
					this->initWithFile("stone_middle.png");
					score = 20;
					weight = 20;
				}
				break;
			case Item_large:
				{
					this->initWithFile("stone_large.png");
					score = 40;
					weight = 40;
				}
				break;
			default:
				break;
			}
		}
		break;
	case Item_gold:
		{
			switch (spriteSize)
			{
			case Item_small:
				{
					this->initWithFile("gold_small.png");
					score = 100;
					weight = 10;
				}
				break;
			case Item_middle:
				{
					this->initWithFile("gold_middle.png");
					score = 200;
					weight = 20;
				}
				break;
			case Item_large:
				{
					this->initWithFile("gold_large.png");
					weight = 40;
					score = 400;
				}
				break;

			default:
				break;
			}
		}
		break;
	case Item_diamond:
		{
			switch (spriteSize)
			{
			case Item_small:
				{
					this->initWithFile("diamond_small.png");
					score = 200;
					weight = 10;
				}
				break;
			case Item_middle:
				{
					this->initWithFile("diamond_middle.png");
					score = 400;
					weight = 20;
				}
				break;
			case Item_large:
				{
					this->initWithFile("diamond_large.png");
					score = 800;
					weight = 40;
				}
				break;
			default:
				break;
			}
		}
		break;
	case Item_secret:
		{
			switch (spriteSize)
			{
			case Item_small:
				{
					this->initWithFile("secret_small.png");
					score = 300;
					weight = 10;
				}
				break;
			case Item_middle:
				{
					this->initWithFile("secret_middle.png");
					score = 600;
					weight = 20;
				}
				break;
			case Item_large:
				{
					this->initWithFile("secret_large.png");
					score = 900;
					weight = 40;
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
