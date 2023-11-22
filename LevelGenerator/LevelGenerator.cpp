#include "LevelGenerator.h"
#include "GameArea.h"
#include "CardDescriber/CardDescriber.h"

USING_NS_CC;

void LevelGenerator::Generate()
{
    /* 获取当前区域信息 */
    GameArea curArea = GameArea::GetInfo(GameSettleUp::GetInstance().currentArea);
    
    /* 按区域生成怪物 */
    GameSettleUp::GetInstance().monsterActors.clear();
    int needGenerateMonsterNum = (random() % curArea.monsterMaxNum) + 1;
    for (int index = 0; index < needGenerateMonsterNum; ++index) {
        ActorName monsterName = curArea.monsters[random() % curArea.monsters.size()];
        GameSettleUp::GetInstance().monsterActors.push_back(ActorFactory::Generate(monsterName));
    }

    /* 按区域生成可能掉落的卡牌 */
    GameSettleUp::GetInstance().dropCards.clear();
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::HPAddCard));
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::AttackAddCard));
    GameSettleUp::GetInstance().dropCards.push_back(Card::Get(CardDescriber::DefenseAddCard));
    
    /* 设置游戏的状态 */
    GameSettleUp::GetInstance().stage = GameStage::BATTLE_STATUS;
    return;
}
