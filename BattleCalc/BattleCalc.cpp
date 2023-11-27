// ReSharper disable CppMemberFunctionMayBeConst
#include "BattleCalc.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

void BattleCalc::Calc()
{
    auto &players = GameSettleUp::GetInstance().playerActors;
    auto &monsters = GameSettleUp::GetInstance().monsterActors;

    // 如果需要的话，对Actor的进攻进行重置
    ResetActorAttackStatus(players, monsters);

    // 选择一个首要进攻Actor
    int actorId = playerRound ? PickRandomAttacker(players, playerRandomNum) :
        PickRandomAttacker(monsters, monsterRandomNum);

    // 进行战斗细节计算
    BattleDetail detail = playerRound ? CalcBattleDetails(actorId, players, monsters) :
        CalcBattleDetails(actorId, monsters, players);

    GameSettleUp::GetInstance().curBattleDetails = detail;
    GameSettleUp::GetInstance().stage = GameStage::PREPARE_ANIMATION_STATUS;

    // 交换下次的攻击发起方
    playerRound = !playerRound;
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

int BattleCalc::PickRandomAttacker(std::map<int, Actor> &attackers, int randomNum)
{
    int curNum = 0;
    int pickNum = random() % randomNum;
    for (auto &actor : attackers) {
        if ((actor.second.canAttack) && (curNum++ == pickNum)) {
            actor.second.canAttack = false;
            return actor.first;
        }
    }

    return -1;
}

int BattleCalc::PickRandomEnemy(const std::map<int, Actor> &enemies)
{
    int curNum = 0;
    int randomNum = random() % enemies.size();
    for (const auto &actor : enemies) {
        if (curNum++ == randomNum) {
            return actor.first;
        }
    }
}

BattleDetail BattleCalc::CalcBattleDetails(int actorId, std::map<int, Actor> &attackers, std::map<int, Actor> &defenders)
{
    BattleDetail detail;
    detail.attackActors.push_back(actorId);
    // 先获取到攻击方式
    detail.attackType = attackers[actorId].GetAttackType();
    if (detail.attackType == AttackType::COMMON) { // 普攻
        int defender = PickRandomEnemy(defenders);
        detail.defenseActors.push_back({defender, attackers[actorId].GetDamageValue(defenders[defender])});
    } else {
        log("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }
    
    return detail;
}

std::string BattleDetail::GetLog() const
{
    std::string logContent = "[Battle Details] Attacker (";
    for (const auto &id : attackActors) {
        logContent += std::to_string(id);
        logContent += " ";
    }
    logContent = logContent.substr(0, logContent.length() - 1);
    logContent += ") Attack Defenders (";

    for (const auto &id : defenseActors) {
        const auto &actor = GameSettleUp::GetInstance().GetActorById(id.first);
        logContent += std::to_string(id.first);
        logContent += "(HP:";
        logContent += std::to_string(actor.HP + id.second);
        logContent += "->";
        logContent += std::to_string(actor.HP);
        logContent += " ";
    }
    logContent = logContent.substr(0, logContent.length() - 1);
    logContent += ")";
    return logContent;
}
