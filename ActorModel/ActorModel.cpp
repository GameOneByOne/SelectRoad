#include "ActorModel.h"
#include <map>
#include <functional>

#include "BattleCalc/BattleCalc.h"
#include "GameDeclare/AnimDeclare.h"
#include "GameDeclare/DefineDeclare.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

namespace {
ActorModel GetDefaultModel()
{
    INIT_ONCE_BEGIN(ActorModel)
    object.HPRange = {0, 0};
    object.attackRange = {0, 0};
    object.defenseRange = {0, 0};
    object.luckRange = {0, 0};
    object.duckRange = {0, 0};
    object.coolnessRange = {0, 0};
    object.canAttackTypes = {};

    object.idleAnim = GameDeclare::Anim::AnimInfo();
    object.hurtAnim = GameDeclare::Anim::AnimInfo();
    object.meleeAttackAnim = GameDeclare::Anim::AnimInfo();
    INIT_ONCE_END()
    return object;
}

ActorModel GetPlayerModel()
{
    INIT_ONCE_BEGIN(ActorModel)
    object.HPRange = {150, 170};
    object.attackRange = {10, 20};
    object.defenseRange = {10, 20};
    object.luckRange = {10, 20};
    object.duckRange = {10, 20};
    object.coolnessRange = {10, 20};
    object.canAttackTypes = {AttackType::COMMON};
    
    object.idleAnim = GameDeclare::Anim::playerIdleAnim;
    object.hurtAnim = GameDeclare::Anim::playerHurtAnim;
    object.meleeAttackAnim = GameDeclare::Anim::playerAttackAnim;
    INIT_ONCE_END()
    return object;
}

ActorModel GetMonsterOneModel()
{
    INIT_ONCE_BEGIN(ActorModel)
    object.HPRange = {12, 35};
    object.attackRange = {5, 10};
    object.defenseRange = {5, 10};
    object.luckRange = {5, 10};
    object.duckRange = {5, 10};
    object.coolnessRange = {5, 10};
    object.canAttackTypes = {AttackType::COMMON};

    object.idleAnim = GameDeclare::Anim::golemIdleAnim;
    object.hurtAnim = GameDeclare::Anim::golemHurtAnim;
    object.meleeAttackAnim = GameDeclare::Anim::golemAttackAnim;
    INIT_ONCE_END()
    return object;
}

const std::map<ActorName, std::function<ActorModel(void)>> ACTOR_MODEL_MAP = {
    {ActorName::DEFAULT, GetDefaultModel},
    {ActorName::PLAYER, GetPlayerModel},
    {ActorName::MONSTER_ONE, GetMonsterOneModel}

};
}

Actor ActorFactory::Generate(const ActorName &name)
{
    ActorModel model = GetActorModel(name);
    return CreateActor(model);
}

ActorModel ActorFactory::GetActorModel(const ActorName &name)
{   
    const auto iter = ACTOR_MODEL_MAP.find(name);
    return iter->second();
}

Actor ActorFactory::CreateActor(const ActorModel &model)
{
    // 用于每个Actor的唯一标识生成
    static int actorId = 0;

    // 使用对应的actorModel里指定的数值范围，来生成出一个随机属性的Actor
    Actor genActor;
    genActor.id = ++actorId;
    genActor.HP = GameUtils::GetRandomFromRange(model.HPRange);
    genActor.HPMax = genActor.HP;
    genActor.attack = GameUtils::GetRandomFromRange(model.attackRange);
    genActor.defense = GameUtils::GetRandomFromRange(model.defenseRange);
    genActor.coolness = GameUtils::GetRandomFromRange(model.coolnessRange);
    genActor.duck = GameUtils::GetRandomFromRange(model.duckRange);
    genActor.luck = GameUtils::GetRandomFromRange(model.luckRange);
    genActor.canAttackTypes = model.canAttackTypes;
    genActor.idleAnim = model.idleAnim;
    genActor.hurtAnim = model.hurtAnim;
    genActor.meleeAttackAnim = model.meleeAttackAnim;
    return genActor;
}
