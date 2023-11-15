#include "LevelGenerator.h"
#include "LevelGenerator/GameArea.h"
#include "CardDescriber/CardDescriber.h"

USING_NS_CC;

void LevelGenerator::Generate()
{
    /* 按区域生成一个怪物 */
    GameSettleUp::GetInstance().monsterActors.clear();
    GameSettleUp::GetInstance().monsterActors.push_back(Actor::Create(ActorModel::MONSTER_TWO));

    /* 按区域生成可能掉落的卡牌 */
    GameSettleUp::GetInstance().dropCards.clear();
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::HPAddCard));
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::AttackAddCard));
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::DefenseAddCard));

    /* 设置游戏的状态 */
    GameSettleUp::GetInstance().stage = GameStage::BATTLE_STATUS;
    return;
}
