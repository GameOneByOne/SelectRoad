#include "Actor.h"

USING_NS_CC;

AttackType Actor::GetAttackType() const
{
    int randomNum = cocos2d::random() % canAttackTypes.size();
    for (const auto &attacktype : canAttackTypes) {
        if (randomNum-- == 0) {
            return attacktype;
        }
    }
}

int Actor::GetDamageValue(const Actor &enemy) const
{
    return MAX(0, attack - static_cast<int>(enemy.defense * 0.4f));
}
