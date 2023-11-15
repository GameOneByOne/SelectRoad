#include "CardDescriber.h"
#include <map>
#include "GameDeclare/DefineDeclare.h"
#include "GameDeclare/ImageDeclare.h"

namespace {
Card InitHPAddCard()
{
    INIT_ONCE_BEGIN(Card)

    object.imagePath = GameDeclare::Image::HPAdditionImage.path;
    object.name = "HP Addition";
    object.level = CardLevel::ONE;
    object.type = CardType::ADDITION;
    object.HPAddition = 100;
    object.describe = "HP Addition.";
    INIT_ONCE_END();
    return object;
}

Card InitAttackAddCard()
{
    INIT_ONCE_BEGIN(Card)

    object.imagePath = GameDeclare::Image::attackAdditionImage.path;
    object.name = "Attack Addition";
    object.level = CardLevel::ONE;
    object.type = CardType::ADDITION;
    object.attackAddition = 3;    
    
    object.describe = "Attack Addition.";
    INIT_ONCE_END();
    return object;
}

Card InitDefenseAddCard()
{
    INIT_ONCE_BEGIN(Card)

    object.imagePath = GameDeclare::Image::defenseAdditionImage.path;
    object.name = "Defense Addition";
    object.level = CardLevel::ONE;
    object.type = CardType::ADDITION;
    object.defenseAddition = 2;
    object.describe = "Defense Addition.";
    INIT_ONCE_END();
    return object;
}
    
const std::map<CardDescriber, std::function<Card(void)>> g_cardInfoMap = {
    {CardDescriber::HPAddCard, InitHPAddCard},
    {CardDescriber::AttackAddCard, InitAttackAddCard},
    {CardDescriber::DefenseAddCard, InitDefenseAddCard}
};
}

Card Card::Get(CardDescriber cardDescriber)
{
    auto iter = g_cardInfoMap.find(cardDescriber);
    if (iter == g_cardInfoMap.end()) {
        return Card();
    }

    return iter->second();
}
