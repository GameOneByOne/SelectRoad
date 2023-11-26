#include "BattleLayer.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "ActorModel/ActorModel.h"
#include "GameDeclare/AnimDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

ActorSprite *ActorSprite::Create(int actorId, bool flipX)
{
    auto pRet = new (std::nothrow) ActorSprite();
    if (pRet && pRet->Init(actorId, flipX)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ActorSprite::Init(int actorId, bool flipX)
{
    if (!init()) {
        return false;
    }

    // 通过Id获取到实际的Actor信息
    id = actorId;
    const Actor &actor = GameSettleUp::GetInstance().GetActorById(actorId);
    setScale(0.25f);
    setFlippedX(flipX);
    setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);

    // 初始化Actor动画
    idleAnim = GameUtils::GetAnimate(actor.idleAnim);
    runAnim = GameUtils::GetAnimate(actor.runAnim);
    hurtAnim = GameUtils::GetAnimate(actor.hurtAnim, 0.05f, 1);
    meleeAttackAnim = GameUtils::GetAnimate(actor.meleeAttackAnim, 0.05f, 1);
    idleAnim->retain();
    runAnim->retain();
    hurtAnim->retain();
    meleeAttackAnim->retain();
    return true;
}

void ActorSprite::Idle()
{
    Animate *anim = idleAnim->clone();
    anim->setTag(ANIM_TAG::IDLE);
    runAction(anim);
    return;
}

void ActorSprite::Run()
{
    Animate *anim = runAnim->clone();
    anim->setTag(ANIM_TAG::RUN);
    runAction(anim);
    return;
}

BattleLayer *BattleLayer::InitLayer()
{
    auto pRet = new (std::nothrow) BattleLayer();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool BattleLayer::Init()
{
    if (!Layer::init()) {
        return false;
    }

    // 计算Actor会生成的位置
    playersPlaceArea.first.x = GameDeclare::Size::screen.width / 12.0f;
    playersPlaceArea.first.y = GameDeclare::Size::screen.height / 3.0f;
    playersPlaceArea.second.x = GameDeclare::Size::screen.width / 12.0f + GameDeclare::Size::screen.width / 3.0f;
    playersPlaceArea.second.y = GameDeclare::Size::screen.height / 3.0f * 2.0f;

    monsterPlaceArea.first.x = GameDeclare::Size::screen.width / 4.0f + GameDeclare::Size::screen.width / 3.0f;
    monsterPlaceArea.first.y = GameDeclare::Size::screen.height / 3.0f;
    monsterPlaceArea.second.x = GameDeclare::Size::screen.width / 12.0f * 11.0f;
    monsterPlaceArea.second.y = GameDeclare::Size::screen.height / 3.0f * 2.0f;
    return true;
}

ActorSprite *BattleLayer::GetActorNodeById(int id) const
{
    auto iter = players.find(id);
    if (iter != players.end()) {
        return iter->second;
    }

    iter = monsters.find(id);
    return iter->second;
}

void BattleLayer::PlaceActor()
{
    /* 生成玩家角色 */
    for (const auto &actor : GameSettleUp::GetInstance().playerActors) {
        // 重复的玩家角色，不在放置
        if (players.find(actor.first) != players.end()) {
            continue;
        }

        ActorSprite *actorNode = ActorSprite::Create(actor.first, false);
        // 生成一定范围内随机的X位置和Y位置，然后放置这个Actor
        float x = GameUtils::GetRandomFromRangeF({playersPlaceArea.first.x, playersPlaceArea.second.x});
        float y = GameUtils::GetRandomFromRangeF({playersPlaceArea.first.y, playersPlaceArea.second.y});
        actorNode->setPosition(x, y);
        players[actor.first] = actorNode;
        actorNode->Idle();
        addChild(actorNode);
        log("[Battle Layer] Players place in [id=%d, x=%f, y=%f]", actor.first, x, y);
    }

    /* 生成怪物角色位置 */
    for (const auto &actor : GameSettleUp::GetInstance().monsterActors) {
        // 重复的怪物角色，不在放置
        if (monsters.find(actor.first) != monsters.end()) {
            continue;
        }

        ActorSprite *actorNode = ActorSprite::Create(actor.first, true);
        // 生成一定范围内随机的X位置和Y位置，然后放置这个Actor
        float x = GameUtils::GetRandomFromRangeF({monsterPlaceArea.first.x, monsterPlaceArea.second.x});
        float y = GameUtils::GetRandomFromRangeF({monsterPlaceArea.first.y, monsterPlaceArea.second.y});
        actorNode->setPosition(x, y);
        monsters[actor.first] = actorNode;
        actorNode->Idle();
        addChild(actorNode);
        log("[Battle Layer] Monster place in [id=%d, x=%f, y=%f]", actor.first, x, y);
    }
    return;
}

void BattleLayer::PlayBattleDetail()
{
    BattleDetail detail = GameSettleUp::GetInstance().curBattleDetails;
    // 按战斗类型进行不同的操作
    switch (detail.attackType) {
    case AttackType::COMMON:
        PlayCommonAttackBattleDetail(detail);
        break;
    }
    
    return;
}

void BattleLayer::PlayCommonAttackBattleDetail(const BattleDetail &detail)
{
    // 进行普通攻击演绎， 普通攻击 进攻方和防御方都只有一个
    // 先获取到进攻和防御方的引用
    Actor &attackerActor = GameSettleUp::GetInstance().GetActorById(detail.attackActors[0]);
    ActorSprite *attackerNode = GetActorNodeById(detail.attackActors[0]);
    Actor &defenderActor = GameSettleUp::GetInstance().GetActorById(detail.defenseActors[0].first);
    ActorSprite *defenderNode = GetActorNodeById(detail.defenseActors[0].first);
    float damage = detail.defenseActors[0].second;
    Vec2 attackOldPosition = attackerNode->getPosition();

    // 进攻方要做的是 (前进，移动动画)（攻击动画，更新数值及战斗日志），（返回站位，Idle动画）
    CallFunc *stopIdleThenRunAnim = CallFunc::create([&]() {
        ActorSprite *animNode = GetActorNodeById(GameSettleUp::GetInstance().curBattleDetails.attackActors[0]);
        animNode->stopActionByTag(ANIM_TAG::IDLE);
        animNode->Run();
    });
    MoveTo *moveToEnemy = MoveTo::create(0.2f, defenderNode->getPosition());
    Spawn *MoveAndRunAnim = Spawn::create(stopIdleThenRunAnim, moveToEnemy, nullptr);

    CallFunc *stopRunAnim = CallFunc::create([&]() {
        ActorSprite *animNode = GetActorNodeById(GameSettleUp::GetInstance().curBattleDetails.attackActors[0]);
        animNode->stopActionByTag(ANIM_TAG::RUN);
    });
    Animate *attackAnim = attackerNode->GetMeleeAttackAnim();
    CallFunc *updateData = CallFunc::create([&]() {
        defenderActor.HP = MAX(0, defenderActor.HP - damage);
        log("%s", GameSettleUp::GetInstance().curBattleDetails.GetLog().c_str());
    });
    Spawn *AttackAndUpdateAnim = Spawn::create(stopRunAnim, attackAnim, updateData, nullptr);

    MoveTo *moveBack = MoveTo::create(0.2f, attackOldPosition);
    CallFunc *beginRunAnim = CallFunc::create([&]() {
        ActorSprite *animNode = GetActorNodeById(GameSettleUp::GetInstance().curBattleDetails.attackActors[0]);
        animNode->Run();
    });
    Spawn *MoveBackAnim = Spawn::create(moveBack, beginRunAnim, nullptr);
    CallFunc *attackEndAnim = CallFunc::create([&]() {
        isAttackerAnimEnd = true;
        ActorSprite *animNode = GetActorNodeById(GameSettleUp::GetInstance().curBattleDetails.attackActors[0]);
        animNode->stopActionByTag(ANIM_TAG::RUN);
        animNode->Idle();
    });
    
    Sequence *attackSequence = Sequence::create(MoveAndRunAnim, stopRunAnim, AttackAndUpdateAnim, MoveBackAnim, attackEndAnim, nullptr);
    isAttackerAnimEnd = false;

    attackerNode->runAction(attackSequence);
    
    // 防御方要做的是 受伤动画，如果死亡了，还要接着播放死亡动画
    CallFunc *defenderEndAnim = CallFunc::create([&]() {
        isDefenderAnimEnd = true;
    });
    DelayTime *delayAnim = DelayTime::create(0.2f);
    if (defenderActor.HP - damage <= 0) {
        Animate *hurtAnim = defenderNode->GetHurtAnim();
        Sequence *defenderSequence = Sequence::create(delayAnim, hurtAnim, defenderEndAnim, nullptr);
        defenderNode->runAction(defenderSequence);
    } else {
        Animate *hurtAnim = defenderNode->GetHurtAnim();
        Sequence *defenderSequence = Sequence::create(delayAnim, hurtAnim, defenderEndAnim, nullptr);
        defenderNode->runAction(defenderSequence);
    }
    isDefenderAnimEnd = false;
    
    GameSettleUp::GetInstance().stage = GameStage::PLAY_ANIMATION_STATUS;
    return;
}

void BattleLayer::update(float delta)
{
    // 如果动画播放完了，需要重置Actor的Idle动画
    if (!isAttackerAnimEnd || !isDefenderAnimEnd) {
        return;
    }

    GameSettleUp::GetInstance().stage = GameStage::BATTLE_STATUS;
    return;
}
