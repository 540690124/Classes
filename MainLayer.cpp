//
//  MainLayer.cpp
//  GoldMiner3.0
//
//  Created by WF on 15/12/23.
//
//

#include "MainLayer.h"
#include "PauseScene.h"
bool MainLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //游戏暂停按钮
    auto stopMenu=MenuItemImage::create("stopMenu.png", "stopMenu.png");
    stopMenu->setTarget(this, menu_selector(MainLayer::onMenuClick));
    stopMenu->setTag(1);
    
    auto aMenu=CCMenu::create(stopMenu,NULL);
    
    aMenu->setPosition(Vec2::ZERO);
    this->addChild(aMenu);
    stopMenu->setPosition(Point(470,310));
    return true;
}
void MainLayer::onMenuClick(Ref * pSender)
{
    auto item=(MenuItem *)pSender;
    
    if(item->getTag()==1)
    {
        //暂停界面
        
        //得到窗口的大小
        Size visibleSize = Director::getInstance()->getVisibleSize();
        RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);
        
        //遍历当前类的所有子节点信息，画入renderTexture中。
        //这里类似截图。
        renderTexture->begin();
        this->getParent()->visit();
        renderTexture->end();
       // renderTexture->retain();
        
        //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
        Director::getInstance()->pushScene(PauseScene::scene(renderTexture));
        
    }
}



