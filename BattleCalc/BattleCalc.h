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
    COMMON, // 预留攻击类型，方便做以后的游戏模式
};

class BattleDetail {
public:
    std::string GetLog();

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
    void PlayerAttackRound();
    void MonsterAttackRound();
    bool IsActorAllDead(const std::map<int, Actor> &actors);
    void ResetActorAttackStatus(std::map<int, Actor> &players, std::map<int, Actor> &monsters);

    const Actor &PickRandomActor(const std::vector<Actor> &actors);

private:
    bool playerRound = true;
    int playerRandomNum = 0;
    int monsterRandomNum = 0;
};
