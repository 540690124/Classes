#include "GameOver.h"
#include "GameLayer.h"



Scene * GameOver::scene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto gameOverLabel = Label::createWithSystemFont("Game Over","Marker Felt.ttf",50);
	gameOverLabel->setPosition(240,200);
	gameOverLabel->setColor(Color3B::RED);
	addChild(gameOverLabel);

	auto item1 = MenuItemFont::create("New Game");
	item1->setCallback(CC_CALLBACK_0(GameOver::newCallBack,this));
	item1->setColor(Color3B::GREEN);

	auto item2 = MenuItemFont::create("Continue");
	item2->setCallback(CC_CALLBACK_0(GameOver::continueCallBack,this));
	item2->setColor(Color3B::GREEN);

	auto item3 = MenuItemFont::create("Exit");
	item3->setCallback(CC_CALLBACK_0(GameOver::exitCallBack,this));
	item3->setColor(Color3B::GREEN);

	auto menu = Menu::create(item1,item2,item3,NULL);
	menu->setPosition(Vec2(240,120));
	menu->alignItemsHorizontallyWithPadding(20);
	addChild(menu);

	return true;
}

void GameOver::exitCallBack()
{
	Director::getInstance()->end();
}

void GameOver::newCallBack()
{
	extern int Level;
	extern int TotalScore;
	TotalScore = 0;
	Level = 1;

	auto scene = GameLayer::scene();
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0,scene));
}

void GameOver::continueCallBack()
{
    extern int Level;
    extern int TotalScore;
    TotalScore = 0;
    Level = 1;
    
    auto scene = GameLayer::scene();
    Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.0,scene));
}


