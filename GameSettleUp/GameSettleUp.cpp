#include "GameSettleUp.h"
#include <cocos2d.h>

USING_NS_CC;

void GameSettleUp::Init()
{
    /* 初始化所有游戏设置 */
    currentArea = AreaName::LOST_FOREST;
    stage = GameStage::LEVEL_GENERATE_STATUS;
    playerActors.clear();
    playerActors.push_back(ActorFactory::Generate(ActorName::PLAYER));
    log("[GameSettleUp] Game SettleUp Machine init finished.");
    return;
}

void GameSettleUp::SettleUp()
{
    stage = GameStage::BEGIN_SELECT_STATUS;
    return;
}

void GameSettleUp::UnInit()
{
    return;
}

void GameSettleUp::ShowSelect()
{
    stage = GameStage::LEVEL_GENERATE_STATUS;
    return;
}
