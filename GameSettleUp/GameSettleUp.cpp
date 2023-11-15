#include "GameSettleUp.h"
#include <cocos2d.h>

USING_NS_CC;

void GameSettleUp::Init()
{
    /* 初始化所有游戏设置 */
    currentArea = Area::LOST_FOREST;
    stage = GameStage::LEVEL_GENERATE_STATUS;
    playerActor = Actor::Create(ActorModel::PLAYER);
    return;
}

void GameSettleUp::SettleUp()
{
    log("Game Settle Up -- SettleUp");
    stage = GameStage::BEGIN_SELECT_STATUS;
    return;
}

void GameSettleUp::UnInit()
{
    log("Game Settle Up -- UnInit");
    return;
}

void GameSettleUp::ShowSelect()
{
    log("Game Settle Up -- ShowSelect");
    stage = GameStage::LEVEL_GENERATE_STATUS;
    return;
}
