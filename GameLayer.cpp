#include "GameLayer.h"
#include "Data.h"
#include "GameComplete.h"
#include "GameOver.h"
#include "ShopLayer.h"
#include "MainLayer.h"
GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
	ItemArray->release();//释放物品数组
}

Scene * GameLayer::scene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
    auto layercolor = MainLayer::create();
	scene->addChild(layer);
    scene->addChild(layercolor);

	return scene;
}
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
    
    
    //获取屏幕尺寸
	auto size = Director::getInstance()->getWinSize();

	char bgStr[50];//用来保存图片名称的字符数组
	sprintf(bgStr,"mineBG%d.png",Level);//不同关卡，背景图名字不同
    //创建游戏背景
	auto bg = Sprite::create(bgStr);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	addChild(bg);
    
    //创建物品数组
	ItemArray = __Array::create();
	ItemArray->retain();//数组计数器+1
	this->addItem();

	addSprAndLabel();//添加精灵和标签
    
    //添加矿工
	miner = new Miner();
	miner->setPosition(Vec2(size.width/2,size.height/2));
	addChild(miner);
    
    //添加钩子
	hook = new Hook();
	addChild(hook);
	hook->setPosition(Vec2(size.width/2-2,size.height/2-22));
	hook->runRotate();
    
    //初始化购种物品对象为空
	theCatchItemUnit = NULL;
    
//    //暂停按钮
//    auto stopMenu = MenuItemImage::create("stopMenu.png", "stopMenu.png");
//    stopMenu->setCallback(CC_CALLBACK_1(GameLayer::onMenuPause, this));
//    stopMenu->setPosition(size.width/2,310);
//    auto sMenu = Menu::create(stopMenu,NULL);
//    sMenu->setPosition(Vec2::ZERO);
//    this->addChild(sMenu);
    
	if (BoomNum > 0)//如果购买了炸弹
	{
        //创建炸弹按钮
		auto itemBoom = MenuItemImage::create("article_2001.png","article_2001.png");
        //设置点击炸弹按钮的回调函数
		itemBoom->setCallback(CC_CALLBACK_0(GameLayer::usedBoom,this));
		boomMenu = Menu::create(itemBoom,NULL);
		boomMenu->setPosition(Vec2(300,160));
		addChild(boomMenu);

	}
    //初始化当前时间
	currentTime = TotalTime[Level-1];
    
    //画线
    draw_node = DrawNode::create();
    addChild(draw_node);
    
	return true;
}
/*
//暂停按钮回调函数
void GameLayer::onMenuPause(Ref * pSender)
{
    //获取窗口大小
    auto size = Director::getInstance()->getVisibleSize();
    RenderTexture * renderTexture = RenderTexture::create(size.width, size.height);
    //遍历当前类的所有子节点信息，画入renderTexture中
    //这里类似截图
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    
    //this->pause();
    //将游戏界面暂停，压入场景堆栈。并切换到PauseScene界面
    Director::getInstance()->pushScene(PauseScene::scene(renderTexture));
}
 */
//画线
void GameLayer::draw_line()
{
    //清空上一次所画的线
    draw_node->clear();
    //重新画线
    draw_node->drawLine(Vec2(238,138), hook->getPosition(), Color4F(0, 255, 255, 125));
}
void GameLayer::onEnter()
{
    Layer::onEnter();
    //创建检测钩子是否收回的时间调度器
    schedule(CC_CALLBACK_0(GameLayer::hookIsBack,this),"miner is Run ?");
    
    //创建检测碰撞的时间调度器
    schedule(CC_CALLBACK_0(GameLayer::checkUpHit,this),"checkUpHit");
    //创建物品跟随钩子移动的时间调度器
    schedule(CC_CALLBACK_0(GameLayer::itemUnitFollowHookFunc,this),"itemUnitFollowHookFunc");
    //创建时间调度器，每秒调用一次倒计时函数让时间自减 1
    schedule(CC_CALLBACK_0(GameLayer::TimeCounter,this),1,"TimeCounter");
    //创建画线的时间调度器，每0.1秒调用一次画线函数
    schedule(CC_CALLBACK_0(GameLayer::draw_line, this), 0.1,"drawline");
	
    //注册触摸事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded,this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void GameLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    //获取钩子位置
	Point p = hook->getPosition();
    //获取钩子的角度
	auto rotate = hook->getRotation();
    //当钩子收回到原来位置时
	if (p.x == 238 && p.y == 138)
	{
        //钩子继续摆动
		hook->runTarget();
        //矿工停止动作
		miner->stopAllActions();
		
	}
	if (rotate<=0)//当钩子角度为<=0时
	{
        //矿工执行右动作
		miner->runMinerAction(right);
	}
	else//钩子角度>0时
	{
        //矿工执行左动作
		miner->runMinerAction(left);
	}
}

void GameLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void GameLayer::onExit()
{
    //停止所有回调事件
	this->unscheduleAllCallbacks();
    //移除所有监听事件
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	Layer::onExit();
}

void GameLayer::hookIsBack()
{
	if (hook->isBack)//当钩子收回
	{
        //矿工停止所有动作
		miner->stopAllActions();
	}
}

void GameLayer::addItem()
{
    //添加石头
	int countStone = ItemStoneNumber[Level-1];
	this->addItemWithType(Item_stone,countStone);
    //添加金子
	int countGold = ItemGoldNumber[Level-1];
	this->addItemWithType(Item_gold,countGold);
    //添加钻石
	int countDiamond = ItemDiamondNumber[Level-1];
	this->addItemWithType(Item_diamond,countDiamond);
    //添加神秘物品
	int countSecret = ItemSecretNumber[Level-1];
	this->addItemWithType(Item_secret,countSecret);
}

void GameLayer::addItemWithType(ItemQuaulityType type, int count)
{
    //随机物品的位置和大小
	for(int i = 0;i<count;i++)
	{
		int t = rand()%3;
		ItemUnits * a;
		switch (t)
		{
		case 0:
			{
				a = new ItemUnits(type,Item_small);
				a->setPosition(Tools::getPointWithType(type,Item_small));
				break;
			}
			
		case 1:
			{
				a = new ItemUnits(type,Item_middle);
				a->setPosition(Tools::getPointWithType(type,Item_middle));
				break;
			}
		case 2:
			{
				a = new ItemUnits(type,Item_large);
				a->setPosition(Tools::getPointWithType(type,Item_large));
				break;
			}
		default:
			break;
		}
		this->addChild(a);
		ItemArray->addObject(a);//将所有物品添加到物品数组里
	}
}

void GameLayer::checkUpHit()
{
    //获取屏幕尺寸
	auto winSize = Director::getInstance()->getWinSize();
    //遍历数组
	for (int i = 0;i<(ItemArray->count());i++)
	{
		ItemUnits * a = (ItemUnits *)ItemArray->getObjectAtIndex(i);
        //检测数组中的每一个物品是否与钩子发生碰撞
		if (Tools::isCollsion(a,hook)&&!(a->isCatch)&&!(hook->isCatchItem))//如果发生碰撞
		{
            //钩子状态标识置为 钩中
			hook->isCatchItem = true;
			a->isCatch = true;//物品状态置为被钩中
			this->theCatchItemUnit = (ItemUnits *)a;
			hook->stopAllActions();//钩子停止所有动作
			
			auto start = a->getPosition();//得到物品的起始位置
			auto point = hook->getPosition();//得到钩子的当前位置
			auto distance = sqrt(pow(start.x-point.x,2)+pow(start.y-point.y,2));//求出物品以钩子原点的距离
			auto weight = a->weight;//得到物品重量
			auto time = weight/distance*8;//计算物品被勾回原点的时间
			if (powerRinse)//如果使用体力药水，则时间缩短
			{
				time = weight/distance*6;
			}
            //钩子回到原点的动作
			auto move = MoveTo::create(time,Vec2(238,138));
            //钩子回到原点后移除掉物品的回调函数
			auto func = CallFuncN::create(CC_CALLBACK_1(GameLayer::deleteItemUnit,this,a));
			auto seq = Sequence::create(move,func,NULL);
			hook->runAction(seq);//钩子执行序列动作
		}
	}
}

void GameLayer::deleteItemUnit(Node * sender,ItemUnits * item)
{
    //物品停止所有动作
	item->stopAllActions();
    //钩子停止所有动作
	hook->stopAllActions();
    //钩子继续摆动
	hook->runRotate();
    //分数增加
	TotalScore = TotalScore+item->score;
    //物品下哦那个场景中移除
	item->removeFromParent();
    //矿工停止所有动作
	miner->stopAllActions();
	hook->isCatchItem = false;//钩子的状态置为未钩中
	this->theCatchItemUnit = NULL;//被钩中物品对象置为空

    //更新分数
	char newScore[20];
	sprintf(newScore,"%d",TotalScore);
	totalScoreLabel->setString(newScore);
    
    //物品从数组中移除
	ItemArray->removeObject(item);

}

void GameLayer::itemUnitFollowHookFunc()
{
	if (theCatchItemUnit!=NULL)//如果被钩中物品对象不为空
	{
        //物品角度跟钩子当前角度一致
		theCatchItemUnit->setRotation(hook->getRotation());
		theCatchItemUnit->setAnchorPoint(Vec2(0.5,1));
		hook->setAnchorPoint(Vec2(0.5,0.7));
		theCatchItemUnit->setPosition(hook->getPosition());
		hook->setAnchorPoint(Vec2(0.5,1));
	}
}

void GameLayer::addSprAndLabel()
{
	//添加各种精灵和标签
	alarmClock = Sprite::create("clockPlate.png");
	alarmClock->setPosition(Vec2(380,260));
	addChild(alarmClock);

	char temp1[10];
	sprintf(temp1,"%d",TotalTime[Level-1]);
	alarmClockLabel = Label::createWithSystemFont(temp1,"Marker Felt.ttf",16);
	alarmClockLabel->setPosition(Vec2(420,260));
	alarmClockLabel->setColor(Color3B::BLUE);
	addChild(alarmClockLabel);

	levelNumSpr = Sprite::create("miner_0707.png");
	levelNumSpr->setPosition(Vec2(380,300));
	addChild(levelNumSpr);

	char temp2[10];
	sprintf(temp2,"%d",Level);
	levelNumLabel = Label::createWithSystemFont(temp2,"Marker Felt.ttf",16);
	levelNumLabel->setPosition(Vec2(420,300));
	levelNumLabel->setColor(Color3B::BLUE);
	addChild(levelNumLabel);


	totalScoreSpr = Sprite::create("rmbImage.png");
	totalScoreSpr->setPosition(Vec2(50,255));
	addChild(totalScoreSpr);

	char temp3[10];
	sprintf(temp3,"%d",TotalScore);
	totalScoreLabel = Label::createWithSystemFont(temp3,"Marker Felt.ttf",16);
	totalScoreLabel->setPosition(Vec2(90,255));
	totalScoreLabel->setColor(Color3B::BLUE);
	addChild(totalScoreLabel);

	goalScoreSpr = Sprite::create("Gold.png");
	goalScoreSpr->setPosition(Vec2(50,300));
	addChild(goalScoreSpr);

	char temp4[10];
	sprintf(temp4,"%d",goalTotalScore[Level-1]);
	goalScoreLabel = Label::createWithSystemFont(temp4,"Marker Felt.ttf",16);
	goalScoreLabel->setPosition(Vec2(90,300));
	goalScoreLabel->setColor(Color3B::BLUE);
	addChild(goalScoreLabel);
}

void GameLayer::TimeCounter()
{
    //当前时间自减 1
	currentTime--;
	char time[10];
	sprintf(time,"%d",currentTime);
	alarmClockLabel->setString(time);//时间标签更新
	if (currentTime<=10)//当时间小于10秒
	{
        //闹钟摆动 时间标签闪烁
		auto rotate1 = RotateTo::create(0.1,10);
		auto rotate2 = RotateTo::create(0.1,-10);
		auto seq = Sequence::create(rotate1,rotate2,NULL);
		auto forever = RepeatForever::create(seq);
		alarmClock->runAction(forever);

		auto blink = Blink::create(1.0f,1);
		auto repeat = RepeatForever::create(blink);
		alarmClockLabel->runAction(repeat);
	}
	if (currentTime==0)//当时间减为 0
	{
        //清除所有内容
		this->removeAllChildren();
		this->removeFromParent();

		if (TotalScore>=goalTotalScore[Level-1])//如果分数达到目标分数
		{
			if (Level == TotalLevels)//并且当前关卡等于总关卡数
			{
				log("succeed!!!");
                //通关
				Director::getInstance()->replaceScene(TransitionMoveInB::create(0.5,GameComplete::scene()));
			}
			else//当前关卡数不等于总关卡数
			{
                //跳到商店界面
				log("store!!!");
				BoomNum = 0;
				powerRinse = false;
				auto scene = ShopLayer::scene();
				Director::getInstance()->replaceScene(TransitionRotoZoom::create(1.0f,scene));
				Level++;//关卡数自加 1
			}
		}
		else//如果当前分数没有达到目标分数
		{
			log("failed!!!");
			//游戏失败
			Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5,GameOver::scene()));
		}
	}
}
//使用炸弹的回调函数
void GameLayer::usedBoom()
{
	if (hook->isCatchItem)//如果钩子钩中物品，才能使用炸弹
	{
		hook->isCatchItem = false;
		BoomNum--;//炸弹数量自减 1
		if (BoomNum == 0)//当炸弹数量为 0
		{
			boomMenu->removeFromParent();//炸弹按钮从场景中移除
		}
		ItemUnits * item;
		for (int i = 0;i<(ItemArray->count());i++)
		{
			item = (ItemUnits *)ItemArray->getObjectAtIndex(i);
			if (item->isCatch)
			{
				break;
			}
		}
		auto p = item->getPosition();
		item->stopAllActions();
		ItemArray->removeObject(item);

		auto boomSpr = Sprite::create("article_2001.png");
		boomSpr->setPosition(Vec2(240,160));
		addChild(boomSpr);

		auto moveTo = MoveTo::create(0.1,p);
		auto func = CallFuncN::create(CC_CALLBACK_1(GameLayer::remove,this,item));
		auto funcc = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeSelf,this,boomSpr));
		auto seq = Sequence::create(moveTo,func,funcc,NULL);
		boomSpr->runAction(seq);
		
		hook->stopAllActions();
		auto func1 = CallFunc::create(CC_CALLBACK_0(GameLayer::stopMinerAction,this));
		auto func2 = CallFunc::create(CC_CALLBACK_0(Hook::runBack,hook));
		auto hookSeq = Sequence::create(func2,DelayTime::create(2),func1,NULL);
		hook->runAction(hookSeq);

		this->boomSpecialEfficiency(p);
	}
}

void GameLayer::remove(Node * sender, ItemUnits * item)
{
    //物品从场景中移除
	item->removeFromParent();
}

void GameLayer::stopMinerAction()
{
    //矿工停止动作
	miner->stopAllActions();
}

void GameLayer::boomSpecialEfficiency(Vec2 point)
{
    //给炸弹添加爆炸特效
	ParticleSystemQuad * mSystem2 = ParticleSystemQuad::create("Boom.plist");
	mSystem2->setTextureWithRect(
								Director::getInstance()->getTextureCache()->addImage("fire.png"),
								Rect(0,0,32,32));
	mSystem2->setBlendAdditive(true);
	mSystem2->setPosition(point);
	addChild(mSystem2);
	mSystem2->setAutoRemoveOnFinish(true);
}

void GameLayer::removeSelf(Node * sender, Sprite * boom)
{
    //炸弹从场景中移除
	boom->removeFromParent();
}
