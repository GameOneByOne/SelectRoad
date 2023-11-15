#include "BattleCalc.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

void BattleCalc::Calc()
{
    battleDetails.clear();
    player = GameSettleUp::GetInstance().playerActor;
    monsters = GameSettleUp::GetInstance().monsterActors;
    while (!IsPlayerDead() && !IsMonsterDead()) {
        BattleDetail detail;
        /* 每回合战斗有被偷袭的概率，被偷袭之后由怪物先手，该概率与冷静值有关 */
        if (BySurpriseAttack()) {
            MonsterAttackRound();
            PlayerAttackRound();
        } else {
            PlayerAttackRound();
            MonsterAttackRound();
        }
    }
    
    /* 战斗结束，则改变游戏状态机 */
    GameSettleUp::GetInstance().curBattleDetails = battleDetails;
    GameSettleUp::GetInstance().stage = GameStage::ANIMATION_STATUS;
    return;
}

void BattleCalc::PlayerAttackRound()
{
    /* 玩家攻击回合 */
    for (auto &monster : monsters) {
        if ((monster.HP == 0) || (player.HP == 0)) {
            continue;
        }
        monster.HP = MAX(monster.HP - player.attack, 0);
        BattleDetail detail;
        detail.isPlayerRound = true;
        detail.curPlayer = player;
        detail.curMonsters = monsters;
        battleDetails.push_back(detail);
        break;
    }

    return;
}

void BattleCalc::MonsterAttackRound()
{
    /* 怪物攻击回合 */
    for (auto &monster : monsters) {
        if ((monster.HP == 0) || (player.HP == 0)) {
            continue;
        }
        player.HP = MAX(player.HP - monster.attack, 0);
        BattleDetail detail;
        detail.isPlayerRound = false;
        detail.curPlayer = player;
        detail.curMonsters = monsters;
        battleDetails.push_back(detail);
    }

    return;
}

bool BattleCalc::IsPlayerDead()
{
    if (player.HP == 0) {
        return true;
    }
    return false;
}

bool BattleCalc::IsMonsterDead()
{
    for (const auto &monster : monsters) {
        if (monster.HP > 0) {
            return false;
        }
    }
    return true;
}

bool BattleCalc::BySurpriseAttack()
{
    return false;
}

