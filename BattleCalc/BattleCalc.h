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
    AttackRound round; // 标识是谁的攻击回合
    AttackType attackType; // 本次攻击回合的攻击方式
    std::vector<int> attackActors; // 攻击方ID，可能多个
    std::vector<std::pair<int, int>> defenseActors; // 防御方<ID, 掉血值>，可能多个
};

class CommonAttackBattleInfo : public BattleDetail {
    ;
};

class BattleCalc {
    DECLARE_SINGLETON(BattleCalc)

public:
    void Calc();
    
private:
    void PlayerAttackRound();
    void MonsterAttackRound();
    
    bool IsPlayerAllDead();
    bool IsMonsterAllDead();

    const Actor &PickRandomActor(const std::vector<Actor> &Actors);

private:
    std::vector<Actor> players;
    std::vector<Actor> monsters;
    std::vector<BattleDetail> battleDetails;
};
