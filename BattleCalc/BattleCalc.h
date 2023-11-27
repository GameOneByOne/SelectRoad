#pragma once

#include <vector>
#include "cocos2d.h"
#include "GameDeclare/DefineDeclare.h"

class Actor;

enum class AttackRound {
    PLAYER,
    MONSTER,
};

enum class AttackType {
    COMMON = 0, // 预留攻击类型，方便做以后的游戏模式
};

class BattleDetail {
public:
    std::string GetLog() const;

public:
    AttackType attackType; // 本次攻击回合的攻击方式
    std::vector<int> attackActors; // 攻击方ID，可能多个
    std::vector<std::pair<int, int>> defenseActors; // 防御方<ID, 掉血值>，可能多个
};

class BattleCalc {
    DECLARE_SINGLETON(BattleCalc)

public:
    void Calc();
    
private:
    void ResetActorAttackStatus(std::map<int, Actor> &players, std::map<int, Actor> &monsters);
    int PickRandomEnemy(const std::map<int, Actor> &enemies);
    int PickRandomAttacker(std::map<int, Actor> &attackers, int randomNum);
    
    BattleDetail CalcBattleDetails(int actorId, std::map<int, Actor> &attackers, std::map<int, Actor> &defenders);

private:
    bool playerRound = true;
    int playerRandomNum = 0;
    int monsterRandomNum = 0;
};
