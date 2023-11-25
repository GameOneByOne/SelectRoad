// ReSharper disable CppMemberFunctionMayBeConst
#include "BattleCalc.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

void BattleCalc::Calc()
{
    BattleDetail detail;
    auto &players = GameSettleUp::GetInstance().playerActors;
    auto &monsters = GameSettleUp::GetInstance().monsterActors;

    // 如果需要的话，对Actor的进攻进行重置
    ResetActorAttackStatus(players, monsters);

    if (IsActorAllDead(players) || IsActorAllDead(monsters)) {
        /* 战斗结束 */
        GameSettleUp::GetInstance().stage = GameStage::SETTLE_UP_STATUS;
        return;
    }

    // 选择一个首要进攻Actor

    // 按获取到的攻击方式进行下一步处理
    
    return;
}

void BattleCalc::ResetActorAttackStatus(std::map<int, Actor> &players, std::map<int, Actor> &monsters)
{
    // 查看一下玩家是否都已经进行过攻击
    playerRandomNum = 0;
    for (const auto &actor : players) {
        if (actor.second.canAttack) {
            playerRandomNum++;
        }
    }

    // 有必要的话进行重置
    if (playerRandomNum == 0) {
        for (auto &actor : players) {
            actor.second.canAttack = true;
        }
        playerRandomNum = players.size();
    }

    // 对怪物也进行如此操作
    monsterRandomNum = 0;
    for (const auto &actor : monsters) {
        if (actor.second.canAttack) {
            monsterRandomNum++;
        }
    }

    // 有必要的话进行重置
    if (monsterRandomNum == 0) {
        for (auto &actor : monsters) {
            actor.second.canAttack = true;
        }
        monsterRandomNum = monsters.size();
    }
    return;
}

void BattleCalc::PlayerAttackRound()
{
    /* 一个玩家攻击回合，会随机挑选怪物进行战斗 */
    return;
}

void BattleCalc::MonsterAttackRound()
{
    /* 选择一个随机的怪物进行攻击， 也选择一个随机的玩家被攻击 */
    return;
}

const Actor &BattleCalc::PickRandomActor(const std::vector<Actor> &Actors)
{
    return Actors[random() % Actors.size()];
}

bool BattleCalc::IsActorAllDead(const std::map<int, Actor> &actors)
{
    for (const auto &actor : actors) {
        if (actor.second.HP > 0) {
            return false;
        }
    }

    return true;
}
