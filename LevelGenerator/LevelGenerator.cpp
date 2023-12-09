#include "LevelGenerator.h"
#include "GameArea.h"
#include "ItemDescriber/Item.h"

USING_NS_CC;

void LevelGenerator::Generate(const AreaName &areaName)
{
    /* 获取当前区域信息 */
    GameArea curArea = GameArea::GetInfo(areaName);
    
    /* 按区域生成怪物 */
    GameSettleUp::GetInstance().monsterActors.clear();
    int needGenerateMonsterNum = (random() % curArea.monsterMaxNum) + 1;
    for (int index = 0; index < needGenerateMonsterNum; ++index) {
        ActorName monsterName = curArea.monsters[random() % curArea.monsters.size()];
        Actor monsterActor = ActorFactory::Generate(monsterName);
        GameSettleUp::GetInstance().monsterActors[monsterActor.id] = monsterActor;
        log("[LevelGenerator] A monster generate finished. [id=%d, "
            "HP=%d, attack=%d, defense=%d]", monsterActor.id, monsterActor.HP, monsterActor.attack, monsterActor.defense);
    }
    
    log("[LevelGenerator] A new level generate finished. [area=%s, monsterNum=%d]", curArea.name.c_str(),
        needGenerateMonsterNum);
    return;
}
