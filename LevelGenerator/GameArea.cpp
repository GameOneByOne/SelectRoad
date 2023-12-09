#include "GameArea.h"
#include <map>
#include <functional>
#include "ActorModel/ActorModel.h"
#include "..\ItemDescriber\Item.h"
#include "GameDeclare/DefineDeclare.h"

namespace {
GameArea InitLostForestArea()
{   
    INIT_ONCE_BEGIN(GameArea)
    object.monsterMaxNum = 4;
    object.name = "Lost Forest";
    object.describe = "this is lost forest.";
    object.monsters = {ActorName::MONSTER_ONE};
    object.dropItems = {ItemName::A_ITEM, ItemName::B_ITEM, ItemName::C_ITEM};
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

std::vector<std::string> GameArea::GetDropItems()
{
    return dropItems;
}
