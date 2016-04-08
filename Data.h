#pragma once

int Level = 1;//关卡数

int TotalLevels = 3;//总关卡数
//每一关对应的不同物品数量
int ItemStoneNumber[3] = {5,8,10};
int ItemGoldNumber[3] = {5,8,10}; 
int ItemDiamondNumber[3] = {0,2,3};
int ItemSecretNumber[3] = {0,1,2};

//炸弹数量初始为0
int BoomNum = 0;
//体力药水初始为未购买
bool powerRinse = false;

//初始化当前分数为100
int TotalScore = 500;
//每一关对应的通关分数
int goalTotalScore[3] = {600,1000,1200};
//每一关对应的计时时间
int TotalTime[3] = {60,80,100};
