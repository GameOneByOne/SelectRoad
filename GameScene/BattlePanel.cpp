#include "BattlePanel.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "ActorModel/ActorModel.h"
#include "GameDeclare/AnimDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

cocos2d::Layer *BattlePanel::InitLayer()
{
    auto pRet = new (std::nothrow) BattlePanel();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool BattlePanel::Init()
{
    if (!Layer::init()) {
        return false;
    }

    InitPlayer();
    InitMonster();
    return true;
}

void BattlePanel::InitPlayer()
{
    /* 生成玩家角色位置 */
    // player = Sprite::create(GameDeclare::Anim::playerIdleAnim.prefixPath + GameUtils::FormatIndex(0) + GameDeclare::Anim::playerIdleAnim.suffixPath);
    // player->runAction(GameSettleUp::GetInstance().playerActors[0].idleAnim);
    // player->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    // player->setScale(GameDeclare::Size::screen.width / player->getBoundingBox().size.width / 10.0f);
    // player->setPosition({GameDeclare::Size::screen.width / 5.0f, GameDeclare::Size::screen.height * 2.0f / 5.0f});
    // addChild(player, 2);
    return;
}

void BattlePanel::InitMonster()
{
    /* 生成怪物角色位置 */
    // monster = Sprite::create(GameDeclare::Anim::golemIdleAnim.prefixPath + GameUtils::FormatIndex(0) + GameDeclare::Anim::golemIdleAnim.suffixPath);
    // monster->runAction(GameSettleUp::GetInstance().monsterActors[0].idleAnim);
    // monster->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    // monster->setFlippedX(true);
    // monster->setScale(GameDeclare::Size::screen.width / monster->getBoundingBox().size.width / 10.0f);
    // monster->setPosition({GameDeclare::Size::screen.width * 3.0f / 5.0f, GameDeclare::Size::screen.height * 2.0f / 5.0f});
    // addChild(monster, 2);
    return;
}

void BattlePanel::update(float delta)
{
    /* 如果正在进行战斗动画播放，则稍微等一会 */
    if (playerOtherAniRunning || monsterOtherAniRunning) {
        return;
    }

    if (GameSettleUp::GetInstance().curBattleDetails.empty()) {
        /* 检查是否需要改变游戏状态 */
        if (GameSettleUp::GetInstance().stage == GameStage::ANIMATION_STATUS) {
            GameSettleUp::GetInstance().stage = GameStage::SETTLE_UP_STATUS;
        }
        return;
    }

    /* 开始组织战斗动画播放 */
    // const auto &iter = GameSettleUp::GetInstance().curBattleDetails.begin();
    // playersInfo = iter->curPlayers;
    // monstersInfo = iter->curMonsters;
    // if (iter->isPlayerRound) {
    //     /* 玩家依次添加的动画为 玩家向前移动，(玩家攻击，血量变化)，玩家返回原位，更新动画状态 */
    //     auto moveForwardAction = MoveTo::create(0.7f, {monster->getPosition().x - monster->getBoundingBox().size.width / 2.0f, monster->getPosition().y});
    //     auto attackAction = GameSettleUp::GetInstance().playerActors[0].attackAnim;
    //     auto updateInfoAction = CallFunc::create([this]() {
    //         GameSettleUp::GetInstance().playerActors = this->playersInfo;
    //         GameSettleUp::GetInstance().monsterActors = this->monstersInfo;
    //     });
    //     auto spawnAction = Spawn::create(attackAction, updateInfoAction, nullptr);
    //     auto moveBackAction = MoveTo::create(0.7f, {GameDeclare::Size::screen.width / 5.0f, player->getPosition().y});
    //     auto playerEndAction = CallFunc::create([this]() {
    //         this->playerOtherAniRunning = false;
    //     });
    //     
    //     auto seqForPlayer = Sequence::create(moveForwardAction, spawnAction, moveBackAction, playerEndAction, nullptr);
    //     player->stopAllActions();
    //     player->runAction(seqForPlayer);
    //     playerOtherAniRunning = true;
    //
    //     /* 怪物依次添加的动画为 延迟动画， 停止Idle动画， 开始受伤动画 ，开始Idle动画，更新动画状态 */
    //     auto delayAction = DelayTime::create(moveForwardAction->getDuration() + attackAction->getDuration() / 3.0f);
    //     auto stopIdleAction = CallFunc::create([this]() {
    //         this->monster->stopActionByTag(0);
    //     });
    //     auto hurtAction = GameSettleUp::GetInstance().monsterActors[0].hurtAnim;
    //     auto startIdleAction = CallFunc::create([this]() {
    //         this->monster->runAction(GameSettleUp::GetInstance().monsterActors[0].idleAnim);
    //     });
    //     auto monsterEndAction = CallFunc::create([this]() {
    //         this->monsterOtherAniRunning = false;
    //     });
    //     auto seqForMonster = Sequence::create(delayAction, stopIdleAction, hurtAction, startIdleAction, monsterEndAction, nullptr);
    //
    //     monster->runAction(seqForMonster);
    //     monsterOtherAniRunning = true;
    //
    // } else { // 代表是怪物进攻过程
    //     /* 怪物依次添加的动画为 怪物向前移动，(怪物攻击，血量变化)，怪物返回原位，更新动画状态 */
    //     auto moveForwardAction = MoveTo::create(0.7f, {player->getPosition().x + player->getBoundingBox().size.width / 2.0f, player->getPosition().y});
    //     auto attackAction = GameSettleUp::GetInstance().monsterActors[0].attackAnim;
    //     auto updateInfoAction = CallFunc::create([this]() {
    //         GameSettleUp::GetInstance().playerActors = this->playersInfo;
    //         GameSettleUp::GetInstance().monsterActors = this->monstersInfo;
    //     });
    //     auto spawnAction = Spawn::create(attackAction, updateInfoAction, nullptr);
    //     auto moveBackAction = MoveTo::create(0.7f, {GameDeclare::Size::screen.width * 3.0f / 5.0f, player->getPosition().y});
    //     auto monsterEndAction = CallFunc::create([this]() {
    //         this->monsterOtherAniRunning = false;
    //     });
    //     
    //     auto seqForMonster = Sequence::create(moveForwardAction, spawnAction, moveBackAction, monsterEndAction, nullptr);
    //     monster->stopAllActions();
    //     monster->runAction(seqForMonster);
    //     monsterOtherAniRunning = true;
    //
    //     /* 玩家依次添加的动画为 延迟动画， 停止Idle动画， 开始受伤动画 ，开始Idle动画，更新动画状态 */
    //     auto delayAction = DelayTime::create(moveForwardAction->getDuration() + attackAction->getDuration() / 3.0f);
    //     auto stopIdleAction = CallFunc::create([this]() {
    //         this->player->stopActionByTag(0);
    //     });
    //     auto hurtAction = GameSettleUp::GetInstance().playerActors[0].hurtAnim;
    //     auto startIdleAction = CallFunc::create([this]() {
    //         this->player->runAction(GameSettleUp::GetInstance().playerActors[0].idleAnim);
    //     });
    //     auto playerEndAction = CallFunc::create([this]() {
    //         this->playerOtherAniRunning = false;
    //     });
    //     auto seqForPlayer = Sequence::create(delayAction, stopIdleAction, hurtAction, startIdleAction, playerEndAction, nullptr);
    //
    //     player->runAction(seqForPlayer);
    //     playerOtherAniRunning = true;
    // } 

    // GameSettleUp::GetInstance().curBattleDetails.erase(iter);
    
    return;
}

