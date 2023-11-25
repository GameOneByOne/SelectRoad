#include "BattleLayer.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "ActorModel/ActorModel.h"
#include "GameDeclare/AnimDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

ActorNode *ActorNode::InitNode(int actorId, bool flipX)
{
    auto pRet = new (std::nothrow) ActorNode();
    if (pRet && pRet->Init(actorId, flipX)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ActorNode::Init(int actorId, bool flipX)
{
    // 通过Id获取到实际的Actor信息
    id = actorId;
    const Actor &actor = GameSettleUp::GetInstance().GetActorById(actorId);
    spriteActor = Sprite::create();
    spriteActor->setScale(0.25f);
    spriteActor->setFlippedX(flipX);
    spriteActor->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);

    // 初始化Actor动画
    idleAnim = GameUtils::GetAnimate(actor.idleAnim);
    hurtAnim = GameUtils::GetAnimate(actor.hurtAnim);
    meleeAttackAnim = GameUtils::GetAnimate(actor.meleeAttackAnim);
    idleAnim->retain();
    hurtAnim->retain();
    meleeAttackAnim->retain();
    addChild(spriteActor);
    return true;
}

void ActorNode::Idle() const
{
    spriteActor->runAction(idleAnim->clone());
    return;
}
void ActorNode::MeleeAttack() const
{
    spriteActor->runAction(meleeAttackAnim->clone());
    return;
}

void ActorNode::Hurt() const
{
    spriteActor->runAction(hurtAnim->clone());
    return;
}

void ActorNode::update(float delta)
{
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

void BattleLayer::PlaceActor()
{
    /* 生成玩家角色 */
    for (const auto &actor : GameSettleUp::GetInstance().playerActors) {
        // 重复的玩家角色，不在放置
        if (players.find(actor.first) != players.end()) {
            continue;
        }

        ActorNode *actorNode = ActorNode::InitNode(actor.first, false);
        // 生成一定范围内随机的X位置和Y位置，然后放置这个Actor
        float x = GameUtils::GetRandomFromRangeF({playersPlaceArea.first.x, playersPlaceArea.second.x});
        float y = GameUtils::GetRandomFromRangeF({playersPlaceArea.first.y, playersPlaceArea.second.y});
        actorNode->setPosition(x, y);
        players[actor.first] = actorNode;
        actorNode->Idle();
        addChild(actorNode);
    }

    /* 生成怪物角色位置 */
    for (const auto &actor : GameSettleUp::GetInstance().monsterActors) {
        // 重复的怪物角色，不在放置
        if (monsters.find(actor.first) != monsters.end()) {
            continue;
        }

        ActorNode *actorNode = ActorNode::InitNode(actor.first, true);
        // 生成一定范围内随机的X位置和Y位置，然后放置这个Actor
        float x = GameUtils::GetRandomFromRangeF({monsterPlaceArea.first.x, monsterPlaceArea.second.x});
        float y = GameUtils::GetRandomFromRangeF({monsterPlaceArea.first.y, monsterPlaceArea.second.y});
        actorNode->setPosition(x, y);
        monsters[actor.first] = actorNode;
        actorNode->Idle();
        addChild(actorNode);
    }
    return;
}

void BattleLayer::PlayBattleDetails() const
{
    BattleDetail detail = GameSettleUp::GetInstance().curBattleDetails;
    // 按战斗类型进行不同的操作


    GameSettleUp::GetInstance().stage = GameStage::BATTLE_STATUS;
    return;
}

void BattleLayer::update(float delta)
{
    return;
}

