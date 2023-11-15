#pragma once

#include <vector>
#include "cocos2d.h"
#include "GameDeclare/DefineDeclare.h"
#include "ActorModel/ActorModel.h"

struct BattleDetail {
    Actor curPlayer;
    std::vector<Actor> curMonsters;
    bool isPlayerRound;
};

class BattleCalc {
    DECLARE_SINGLETON(BattleCalc)

public:
    void Calc();
    
private:
    void PlayerAttackRound();
    void MonsterAttackRound();

    bool BySurpriseAttack();
    bool IsPlayerDead();
    bool IsMonsterDead();

private:
    Actor player;
    std::vector<Actor> monsters;
    std::vector<BattleDetail> battleDetails;
};
