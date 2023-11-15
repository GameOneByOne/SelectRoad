#include "GameArea.h"
#include <map>
#include <functional>
#include "ActorModel/ActorModel.h"
#include "CardDescriber/CardDescriber.h"
#include "GameDeclare/DefineDeclare.h"

namespace {
GameArea InitLostForestArea()
{   
    INIT_ONCE_BEGIN(GameArea);
    object.name = "Lost Forest";
    object.describe = "this is lost forest.";
    object.actors = {Actor::Create(ActorModel::MONSTER_ONE)};
    object.cards = {Card::Get(CardDescriber::AttackAddCard), Card::Get(CardDescriber::DefenseAddCard), Card::Get(CardDescriber::HPAddCard)};
    INIT_ONCE_END();
    return object;
}

const std::map<Area, std::function<GameArea(void)>> g_areaInfoMap = {
    {Area::LOST_FOREST, InitLostForestArea}
};
}

GameArea GameArea::GetInfo(Area area)
{
    auto iter = g_areaInfoMap.find(area);
    if (iter == g_areaInfoMap.end()) {
        return GameArea();
    }

    return iter->second();
}
