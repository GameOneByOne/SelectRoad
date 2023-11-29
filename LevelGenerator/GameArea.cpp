#include "GameArea.h"
#include <map>
#include <functional>
#include "ActorModel/ActorModel.h"
#include "CardDescriber/CardDescriber.h"
#include "GameDeclare/DefineDeclare.h"

namespace {
GameArea InitLostForestArea()
{   
    INIT_ONCE_BEGIN(GameArea)
    object.monsterMaxNum = 4;
    object.name = "Lost Forest";
    object.describe = "this is lost forest.";
    object.monsters = {ActorName::MONSTER_ONE};
    object.cards = {Card::Get(CardDescriber::AttackAddCard), Card::Get(CardDescriber::DefenseAddCard), Card::Get(CardDescriber::HPAddCard)};
    INIT_ONCE_END()
    return object;
}

const std::map<AreaName, std::function<GameArea(void)>> AREA_INFO_MAP = {
    {AreaName::LOST_FOREST, InitLostForestArea}
};
}

GameArea GameArea::GetInfo(AreaName area)
{
    const auto iter = AREA_INFO_MAP.find(area);
    return iter->second();
}
