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
    setContentSize({45.0f, 67.0f});

    // 初始化Actor动画
    idleAnim = GameUtils::GetAnimate(actor.idleAnim);
    runAnim = GameUtils::GetAnimate(actor.runAnim);
    dyingAnim = GameUtils::GetAnimate(actor.dyingAnim, 0.05f, 1);
    hurtAnim = GameUtils::GetAnimate(actor.hurtAnim, 0.05f, 1);
    meleeAttackAnim = GameUtils::GetAnimate(actor.meleeAttackAnim, 0.05f, 1);
    idleAnim->retain();
    runAnim->retain();
    dyingAnim->retain();
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

void ActorSprite::MeleeAttackToEnemy(const cocos2d::Vec2 &position, float speed)
{
    runningAnim = true;
    Vec2 oldPosition = getPosition();
    // 进攻方要做的是 (前进，移动动画)
    CallFunc *stopIdleThenRunAnim = CallFunc::create([&]() {
        stopActionByTag(ANIM_TAG::IDLE);
        Animate *anim = runAnim->clone();
        anim->setTag(ANIM_TAG::RUN);
        runAction(anim);
    });
    MoveTo *moveToEnemy = MoveTo::create(speed, position);
    Spawn *runToEnemySpawnAnim = Spawn::create(stopIdleThenRunAnim, moveToEnemy, nullptr);

    // 然后是攻击动画
    CallFunc *stopRunAnim = CallFunc::create([&]() {
        stopActionByTag(ANIM_TAG::RUN);
    });
    Spawn *attackEnemySpawnAnim = Spawn::create(stopRunAnim, meleeAttackAnim->clone(), nullptr);

    // 最后是（返回站位，Idle动画）
    MoveTo *moveBackAnim = MoveTo::create(speed, oldPosition);
    CallFunc *beginRunAnim = CallFunc::create([&]() {
        Animate *anim = runAnim->clone();
        anim->setTag(ANIM_TAG::RUN);
        setFlippedX(!isFlippedX());
        runAction(anim);
    });
    Spawn *moveBackAndRunAnim = Spawn::create(moveBackAnim, beginRunAnim, nullptr);
    CallFunc *resetAnim = CallFunc::create([&]() {
        stopActionByTag(ANIM_TAG::RUN);
        setFlippedX(!isFlippedX());
        Animate *anim = idleAnim->clone();
        anim->setTag(ANIM_TAG::IDLE);
        runAction(anim);
        runningAnim = false;
    });
    
    Sequence *runSeq = Sequence::create(runToEnemySpawnAnim, stopRunAnim, attackEnemySpawnAnim, moveBackAndRunAnim, resetAnim, nullptr);
    runAction(runSeq);
    return;
}

void ActorSprite::DamageFromAttacker(int damage, float delayTime)
{
    runningAnim = true;
    // 这里要判断一下受伤之后会不会死亡
    const Actor &actor = GameSettleUp::GetInstance().GetActorById(id);
    bool isDead = actor.HP <= damage;

    // 要先等待延迟
    DelayTime *delayAnim = DelayTime::create(delayTime);

    // 然后是受伤动画和更新HP
    CallFunc *stopIdleAnim = CallFunc::create([&]() {
        stopActionByTag(ANIM_TAG::IDLE);
    });
    CallFunc *updateHPAnim = CallFunc::create([damage, this]() {
        Actor &actorData = GameSettleUp::GetInstance().GetActorById(id);
        actorData.HP = MAX(0, actorData.HP - damage);
    });
    Spawn *UpdateDataAnim = Spawn::create(stopIdleAnim, updateHPAnim, nullptr);

    // 视情况添加死亡动画，并恢复Idle
    if (isDead) {
        CallFunc *resetAnim = CallFunc::create([&]() {
            runningAnim = false;
        });
        Sequence *runSeq = Sequence::create(delayAnim, UpdateDataAnim, dyingAnim->clone(), resetAnim, nullptr);
        runAction(runSeq);
    } else {
        CallFunc *resetAnim = CallFunc::create([&]() {
            Animate *anim = idleAnim->clone();
            anim->setTag(ANIM_TAG::IDLE);
            runAction(anim);
            runningAnim = false;
        });
        Sequence *runSeq = Sequence::create(delayAnim, UpdateDataAnim, hurtAnim->clone(), resetAnim, nullptr);
        runAction(runSeq);
    }
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

void BattleLayer::CleanBattleLayer()
{
    for (auto actorIter = players.begin(); actorIter != players.end();) {
        if (GameSettleUp::GetInstance().IsActorAlive(actorIter->first)) {
            ++actorIter;
        } else {
            FadeOut *fadeOutAnim = FadeOut::create(1.0f);
            actorIter->second->runAction(fadeOutAnim);
            actorIter = players.erase(actorIter);
        }
    }

    for (auto actorIter = monsters.begin(); actorIter != monsters.end();) {
        if (GameSettleUp::GetInstance().IsActorAlive(actorIter->first)) {
            ++actorIter;
        } else {
            FadeOut *fadeOutAnim = FadeOut::create(1.0f);
            actorIter->second->runAction(fadeOutAnim);
            actorIter = monsters.erase(actorIter);
        }
    }
    return;
}

void BattleLayer::PlayBattleDetail()
{
    CleanBattleLayer();
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
    const int animSpeed = 0.5f;
    // 进行普通攻击演绎， 普通攻击 进攻方和防御方都只有一个
    ActorSprite *attackerNode = GetActorNodeById(detail.attackActors[0]);
    ActorSprite *defenderNode = GetActorNodeById(detail.defenseActors[0].first);
    Vec2 enemyPosition = defenderNode->getPosition();

    attackerNode->MeleeAttackToEnemy(enemyPosition, animSpeed);
    defenderNode->DamageFromAttacker(detail.defenseActors[0].second, animSpeed);
    isAnimRunning = true;
    GameSettleUp::GetInstance().stage = GameStage::PLAY_ANIMATION_STATUS;
    return;
}

void BattleLayer::update(float delta)
{
    // 检查动画有没有播放完
    if (isAnimRunning) {
        for (const auto &sprite : players) {
            if (!sprite.second->AnimSequenceDone()) {
                return;
            }
        }
        for (const auto &sprite : monsters) {
            if (!sprite.second->AnimSequenceDone()) {
                return;
            }
        }
        // 打印战斗日志
        log("%s", GameSettleUp::GetInstance().curBattleDetails.GetLog().c_str());
        isAnimRunning = false;
        GameSettleUp::GetInstance().stage = GameStage::SETTLE_UP_STATUS;
    }
    
    return;
}
