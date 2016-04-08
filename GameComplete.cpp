#include "GameComplete.h"



Scene * GameComplete::scene()
{
	auto scene = Scene::create();
	auto layer = GameComplete::create();
	scene->addChild(layer);

	return scene;
}

bool GameComplete::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winLabel = Label::createWithSystemFont("Game Win","Marker Felt.ttf",50);
	winLabel->setColor(Color3B::RED);
	winLabel->setPosition(Vec2(240,160));
	addChild(winLabel);

	auto mSystem = ParticleSystemQuad::create("fengye.plist");
	mSystem->setTextureWithRect(Director::getInstance()->getTextureCache()->addImage("fengye.png"),Rect(0,0,91,91));
	mSystem->setBlendAdditive(true);
	mSystem->setPosition(Vec2(240,160));
	addChild(mSystem);

	auto close = MenuItemImage::create("CloseNormal.png","CloseSelected.png");
	close->setCallback(CC_CALLBACK_1(GameComplete::menuCloseCallBack,this));
	close->setPosition(Vec2(460,20));
	 auto menu = Menu::create(close,NULL);
	 menu->setPosition(Vec2::ZERO);
	 addChild(menu,2);



	return true;
}

void GameComplete::menuCloseCallBack(Ref * pSender)
{
	Director::getInstance()->end();
}
