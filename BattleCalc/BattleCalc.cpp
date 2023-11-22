#include "BattleCalc.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

void BattleCalc::Calc()
{
    battleDetails.clear();
    players = GameSettleUp::GetInstance().playerActors;
    monsters = GameSettleUp::GetInstance().monsterActors;
    while (!IsPlayerAllDead() && !IsMonsterAllDead()) {
        /* 每回合双方只会有一个随机的actor进行攻击，攻击对象也是随机的 */
        PlayerAttackRound();
        MonsterAttackRound();
    }
    
    /* 战斗结束，则改变游戏状态机 */
    GameSettleUp::GetInstance().curBattleDetails = battleDetails;
    GameSettleUp::GetInstance().stage = GameStage::ANIMATION_STATUS;
    return;
}

void BattleCalc::PlayerAttackRound()
{
    /* 一个玩家攻击回合，会随机挑选怪物进行战斗 */
    for (auto &monster : monsters) {
        if ((monster.HP == 0) || (players[0].HP == 0)) {
            continue;
        }
        monster.HP = MAX(monster.HP - players[0].attack, 0);
        BattleDetail detail;
        // detail.isPlayerRound = true;
        // detail.curPlayers = players;
        // detail.curMonsters = monsters;
        // battleDetails.push_back(detail);
        break;
    }

    return;
}

void BattleCalc::MonsterAttackRound()
{
    /* 选择一个随机的怪物进行攻击， 也选择一个随机的玩家被攻击 */
    // Actor &monster = PickRandomActor(monsters);
    // Actor &player = PickRandomActor(players);

    // player.HP = MAX(player.HP - monster.attack, 0);
    // BattleDetail detail;
    // detail.isPlayerRound = false;
    // detail.curPlayers = players;
    // detail.curMonsters = monsters;
    // battleDetails.push_back(detail);
    return;
}

const Actor &BattleCalc::PickRandomActor(const std::vector<Actor> &Actors)
{
    return Actors[random() % Actors.size()];
}

bool BattleCalc::IsPlayerAllDead()
{
    for (const auto &player : players) {
        if (player.HP > 0) {
            return false;
        }
    }

    return true;
}

bool BattleCalc::IsMonsterAllDead()
{
    for (const auto &monster : monsters) {
        if (monster.HP > 0) {
            return false;
        }
    }
    return true;
}
