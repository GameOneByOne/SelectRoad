#include <ActorModel/ActorModel.h>
#include <map>
#include <functional>

#include "GameDeclare/AnimDeclare.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

namespace {


Actor CreatePlayerActor()
{
    Actor genActor;
    genActor.HP = GameUtils::GetRandomFromRange(210, 220);
    genActor.HPMax = genActor.HP;
    genActor.attack = GameUtils::GetRandomFromRange(10, 20);
    genActor.defense = GameUtils::GetRandomFromRange(10, 20);
    genActor.luck = GameUtils::GetRandomFromRange(10, 20);
    genActor.duck = GameUtils::GetRandomFromRange(10, 20);
    genActor.coolness = GameUtils::GetRandomFromRange(10, 20);
    
    genActor.idleAnim = GameUtils::GetAnimate(GameDeclare::Anim::playerIdleAnim, 0.05f, -1);
    genActor.hurtAnim = GameUtils::GetAnimate(GameDeclare::Anim::playerHurtAnim, 0.05f, 1);
    genActor.attackAnim = GameUtils::GetAnimate(GameDeclare::Anim::playerAttackAnim, 0.05f, 1);
    genActor.idleAnim->setTag(0);
    genActor.hurtAnim->setTag(1);
    genActor.attackAnim->setTag(2);
    genActor.idleAnim->retain();
    genActor.hurtAnim->retain();
    genActor.attackAnim->retain();
    return genActor;
}

Actor CreateMonsterOneActor()
{
    Actor genActor;
    genActor.HP = GameUtils::GetRandomFromRange(12, 35);
    genActor.HPMax = genActor.HP;
    genActor.attack = GameUtils::GetRandomFromRange(30, 40);
    genActor.defense = GameUtils::GetRandomFromRange(5, 10);
    genActor.luck = GameUtils::GetRandomFromRange(5, 10);
    genActor.duck = GameUtils::GetRandomFromRange(5, 10);
    genActor.coolness = GameUtils::GetRandomFromRange(5, 10);
    return genActor;
}

Actor CreateMonsterTwoActor()
{
    Actor genActor;
    genActor.HP = GameUtils::GetRandomFromRange(12, 35);
    genActor.HPMax = genActor.HP;
    genActor.attack = GameUtils::GetRandomFromRange(5, 10);
    genActor.defense = GameUtils::GetRandomFromRange(5, 10);
    genActor.luck = GameUtils::GetRandomFromRange(5, 10);
    genActor.duck = GameUtils::GetRandomFromRange(5, 10);
    genActor.coolness = GameUtils::GetRandomFromRange(5, 10);

    genActor.idleAnim = GameUtils::GetAnimate(GameDeclare::Anim::golemIdleAnim, 0.05f, -1);
    genActor.hurtAnim = GameUtils::GetAnimate(GameDeclare::Anim::golemHurtAnim, 0.05f, 1);
    genActor.attackAnim = GameUtils::GetAnimate(GameDeclare::Anim::golemAttackAnim, 0.05f, 1);
    genActor.idleAnim->setTag(0);
    genActor.hurtAnim->setTag(1);
    genActor.attackAnim->setTag(2);
    genActor.idleAnim->retain();
    genActor.hurtAnim->retain();
    genActor.attackAnim->retain();
    return genActor;
}

const std::map<ActorModel, std::function<Actor(void)>> g_actorInfoMap = {
    {ActorModel::PLAYER, CreatePlayerActor},
    {ActorModel::MONSTER_ONE, CreateMonsterOneActor},
    {ActorModel::MONSTER_TWO, CreateMonsterTwoActor}
};
}

Actor Actor::Create(ActorModel model)
{
    auto iter = g_actorInfoMap.find(model);
    if (iter == g_actorInfoMap.end()) {
        return Actor();
    }

    return iter->second();
}

void Actor::AddCard(Card card)
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

void Actor::AddAdditionCard(Card card)
{
    HP = MIN(HP + card.HPAddition, HPMax);
    attack += card.attackAddition;
    defense += card.defenseAddition;
    luck += card.luckAddition;
    duck += card.duckAddition;
    coolness += card.coolnessAddition;
    return;
}
