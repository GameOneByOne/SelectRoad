#include "Actor.h"

void Actor::AddCard(const Card &card)
{
    switch(card.type) {
        case CardType::ADDITION:
            AddAdditionCard(card);
            break;
        default:
            break;
    }
    return;
}

void Actor::AddAdditionCard(const Card &card)
{
    HP = MIN(HP + card.HPAddition, HPMax);
    attack += card.attackAddition;
    defense += card.defenseAddition;
    luck += card.luckAddition;
    duck += card.duckAddition;
    coolness += card.coolnessAddition;
    return;
}

AttackType Actor::GetAttackType() const
{
    return canAttackTypes[cocos2d::random() % canAttackTypes.size()];
}

float Actor::GetDamageValue(const Actor &enemy) const
{
    return MAX(0, static_cast<float>(attack) - static_cast<float>(enemy.defense) * 0.6f);
}
