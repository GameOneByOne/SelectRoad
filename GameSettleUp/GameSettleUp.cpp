#include "GameSettleUp.h"
#include <cocos2d.h>

USING_NS_CC;

void GameSettleUp::Init()
{
    /* 初始化所有游戏设置 */
    currentArea = AreaName::LOST_FOREST;
    stage = GameStage::LEVEL_GENERATE_STATUS;
    playerActors.clear();
    Actor playerActor = ActorFactory::Generate(ActorName::PLAYER);
    playerActors[playerActor.id] = playerActor;
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

const Actor &GameSettleUp::GetActorById(int actorId) const
{
    for (const auto &actor : playerActors) {
        if (actor.first == actorId) {
            return actor.second;
        }
    }

    for (const auto &actor : monsterActors) {
        if (actor.first == actorId) {
            return actor.second;
        }
    }

    return ActorFactory::Generate(ActorName::DEFAULT);
}
