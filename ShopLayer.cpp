#include "ShopLayer.h"
#include "GameLayer.h"

ShopLayer::ShopLayer(void)
{
}


ShopLayer::~ShopLayer(void)
{
	itemArray->release();
	messageArray->release();
}

Scene * ShopLayer::scene()
{
	auto scene = Scene::create();
	auto layer = ShopLayer::create();
	scene->addChild(layer);

	return scene;
}

bool ShopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	isbuy = false;
	selectItemNumber = 0;
	
	auto size = Director::getInstance()->getWinSize();
	auto bg = Sprite::create("shopBack.png");
	bg->setPosition(Vec2(size.width/2,size.height/2));
	addChild(bg);

	
	npc = new TradesWoman();
	npc->setPosition(Vec2(100,200));
	addChild(npc);
	npc->action2();

	
	auto table = Sprite::create("tableImage.png");
	table->setPosition(Vec2(240,65));
	addChild(table);

	
	auto next = MenuItemImage::create("shopArrow.png","shopArrow.png");
	next->setCallback(CC_CALLBACK_0(ShopLayer::goNext,this));
	auto nextMenu = Menu::create(next,NULL);
	nextMenu->setPosition(Vec2(425,30));
	this->addChild(nextMenu);

	
	auto item1 = Sprite::create("qianglishui.png");
	item1->setPosition(Vec2(120,90));
	addChild(item1);
	auto item2 = Sprite::create("article_2001.png");
	item2->setPosition(Vec2(120,70));
	itemArray = __Array::create();
	itemArray->retain();
	itemArray->addObject(item1);
	itemArray->addObject(item2);
	
	howMuch = Label::createWithSystemFont("200","Marker Felt.ttf",16);
	howMuch->setPosition(Vec2(110,45));
	howMuch->setColor(Color3B::YELLOW);
	addChild(howMuch);
	

	
	auto messageBg = Sprite::create("information.png");
	messageBg->setPosition(Vec2(380,280));
	addChild(messageBg);

	auto informationOne = Sprite::create("information1.png");
	informationOne->setPosition(Vec2(380,270));
	auto informationTwo = Sprite::create("information2.png");
	informationTwo->setPosition(Vec2(380,270));
	addChild(informationOne);
	messageArray = __Array::create();
	messageArray->retain();
	messageArray->addObject(informationOne);
	messageArray->addObject(informationTwo);
	

	auto leftBtn = MenuItemImage::create("buyleftbtn.png","buyleftbtn.png");
	leftBtn->setCallback(CC_CALLBACK_0(ShopLayer::leftBtnFunc,this));
	auto rightBtn = MenuItemImage::create("buyrightbtn.png","buyrightbtn.png");
	rightBtn->setCallback(CC_CALLBACK_0(ShopLayer::rightBtnFunc,this));
	auto buyBtn = MenuItemImage::create("buyButton.png","buyButtonSelect.png");
	buyBtn->setCallback(CC_CALLBACK_0(ShopLayer::buyBtnFunc,this));

	auto menu = Menu::create(leftBtn,buyBtn,rightBtn,NULL);
	menu->alignItemsHorizontallyWithPadding(15);
	menu->setPosition(Vec2(110,20));
	addChild(menu);

	auto buyLabel = Label::createWithSystemFont("buy","Marker Felt.ttf",16);
	buyLabel->setPosition(Vec2(29,18));
	buyBtn->addChild(buyLabel);

	return true;
}

void ShopLayer::leftBtnFunc()
{
	int tmp = selectItemNumber;
	char lb[10];
	if (selectItemNumber==0)
	{
		selectItemNumber = itemArray->count()-1;
		sprintf(lb,"%d",300);
		howMuch->setString(lb);
	}
	else
	{
		selectItemNumber--;
		sprintf(lb,"%d",200);
		howMuch->setString(lb);
	}
	log("tmp = %d, selectNum = %d",tmp,selectItemNumber);


	Sprite * t = (Sprite *)itemArray->getObjectAtIndex(tmp);
	t->removeFromParent();
	t = (Sprite *)itemArray->getObjectAtIndex(selectItemNumber);
	this->addChild(t);

	t = (Sprite *)messageArray->getObjectAtIndex(tmp);
	t->removeFromParent();
	t = (Sprite *)messageArray->getObjectAtIndex(selectItemNumber);
	this->addChild(t);
	
}

void ShopLayer::rightBtnFunc()
{
	int temp = selectItemNumber;
	char lb[10];
	if (selectItemNumber == itemArray->count()-1)
	{
		selectItemNumber=0;
		sprintf(lb,"%d",200);
		howMuch->setString(lb);
	}
	else
	{
		selectItemNumber++;
		sprintf(lb,"%d",300);
		howMuch->setString(lb);
	}
	Sprite * t = (Sprite*)itemArray->getObjectAtIndex(temp);
	t->removeFromParent();
	t = (Sprite *)itemArray->getObjectAtIndex(selectItemNumber);
	addChild(t);

	Sprite * m = (Sprite *)messageArray->getObjectAtIndex(temp);
	m->removeFromParent();
	m = (Sprite *)messageArray->getObjectAtIndex(selectItemNumber);
	addChild(m);

}

void ShopLayer::buyBtnFunc()
{
	
	extern int BoomNum;
	extern bool powerRinse;
	extern int TotalScore;
	
	npc->stopAllActions();
	npc->action3();
	
	if (selectItemNumber == 0)
	{
		if (TotalScore>=200)
		{
			powerRinse = true;
			TotalScore -= 200;
			isbuy = true;
		}
		else
		{
			npc->action1();
		}
	}
	else if(selectItemNumber == 1)
	{
		if (TotalScore>=300)
		{
			BoomNum++;
			TotalScore-=300;
			isbuy = true;
		}
		else
		{
			
			npc->action1();
		}
	}
	if (powerRinse)
	{
		log("%i,true",BoomNum);
	}
	else
	{
		log("%i,false",BoomNum);
	}
	
}

void ShopLayer::goNext()
{
	auto func1 = CallFunc::create(CC_CALLBACK_0(ShopLayer::npcAnger ,this));
	auto func2 = CallFunc::create(CC_CALLBACK_0(ShopLayer::gotoNextGame ,this));
	Sequence * seq;
	if (!isbuy)
	{
		seq = Sequence::create(func1,DelayTime::create(3),func2,NULL);
	}
	else
	{
		seq = Sequence::create(func2,NULL);
	}
	this->runAction(seq);
}

void ShopLayer::npcAnger()
{
	npc->stopAllActions();
	npc->action1();
}

void ShopLayer::gotoNextGame()
{
	auto scene = GameLayer::scene();
	Director::getInstance()->replaceScene(scene);
}

