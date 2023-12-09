#include "GameSettleUp.h"
#include <cocos2d.h>
#include "ItemDescriber/ItemFactory.h"

USING_NS_CC;

void GameSettleUp::Init()
{
    /* 初始化所有游戏设置 */
    currentArea = AreaName::LOST_FOREST;
    stage = GameStage::PREPARE_BATTLE_STATUS;
    playerActors.clear();
    Actor playerActor = ActorFactory::Generate(ActorName::PLAYER);
    playerActors[playerActor.id] = playerActor;

    /* 初始化物品工厂 */
    ItemFactory::InitItemFactory();
    log("[GameSettleUp] Game SettleUp Machine init finished.");
    return;
}

void GameSettleUp::SettleUp()
{
    // 清除已经死亡的Actor
    CleanDeadActor();

    // 判断游戏是否结束，查看Actor是否全部阵亡
    if (playerActors.empty()) {
        // 游戏结束
        stage = GameStage::GAMEOVER_STATUS;
    } else if (monsterActors.empty()) {
        // 进入下一关
        stage = GameStage::SELECT_STATUS;
    } else {
        // 继续战斗
        stage = GameStage::BATTLING_STATUS;
    }
    
    return;
}

void GameSettleUp::UnInit()
{
    return;
}

void GameSettleUp::ShowSelect()
{
    stage = GameStage::ENTER_BATTLE_STATUS;
    return;
}

void GameSettleUp::CleanDeadActor()
{
    for (auto actorIter = playerActors.begin(); actorIter != playerActors.end();) {
        if (actorIter->second.HP == 0) {
            actorIter = playerActors.erase(actorIter);
        } else {
            ++actorIter;
        }
    }

    for (auto actorIter = monsterActors.begin(); actorIter != monsterActors.end();) {
        if (actorIter->second.HP == 0) {
            actorIter = monsterActors.erase(actorIter);
        } else {
            ++actorIter;
        }
    }
    return;
}

bool GameSettleUp::IsActorAlive(int actorId)
{
    if ((playerActors.find(actorId) != playerActors.end()) ||
        (monsterActors.find(actorId) != monsterActors.end())) {
        return true;
    }
    return false;
}

Actor &GameSettleUp::GetActorById(int actorId)
{
    for (auto &actor : playerActors) {
        if (actor.first == actorId) {
            return actor.second;
        }
    }

    for (auto &actor : monsterActors) {
        if (actor.first == actorId) {
            return actor.second;
        }
    }

    return ActorFactory::Generate(ActorName::DEFAULT);
}
