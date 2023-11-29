#include "ConductScene.h"
#include <string>

#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "LevelGenerator/LevelGenerator.h"
#include "BattleCalc/BattleCalc.h"

USING_NS_CC;

Scene* ConductScene::Show()
{
    auto pRet = new (std::nothrow) ConductScene();
    if (pRet && pRet->InitScene()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ConductScene::InitScene()
{
    if (!Scene::init()) {
        return false;
    }
    
    /* 初始化界面及游戏结算器， 之后就会进入update函数，开始主逻辑循环 */
    GameSettleUp::GetInstance().Init();

    battleLayer = BattleLayer::InitLayer();
    battleLayer->PlaceActor();

    actorInfoSlideLayer = ActorInfoSlideLayer::InitLayer();
    addChild(battleLayer, 5);
    // addChild(actorInfoSlideLayer,10); // wait for dev.

    InitBeforeBattleMenu();
    InitBattlingMenu();
    scheduleUpdate();
    return true;
}

void ConductScene::InitBeforeBattleMenu()
{
    // 战斗前的菜单组，有查看伙伴信息，打开战斗日志，下一关
    Label *checkPartnerLabel = Label::createWithTTF("查看伙伴信息", GameDeclare::Font::FELT_TTF, 28);
    MenuItemLabel *checkPartnerMenuItem = MenuItemLabel::create(checkPartnerLabel, [this](Ref *ref) -> void {
        log("open partner info.");
    });

    Label *openBattleLogLabel = Label::createWithTTF("打开战斗日志", GameDeclare::Font::FELT_TTF, 28);
    MenuItemLabel *openBattleLogMenuItem = MenuItemLabel::create(openBattleLogLabel, [this](Ref *ref) -> void {
        log("open battle log.");
    });

    Label *nextLevelLabel = Label::createWithTTF("往前走", GameDeclare::Font::FELT_TTF, 28);
    MenuItemLabel *nextLevelMenuItem = MenuItemLabel::create(nextLevelLabel, [this](Ref *ref) -> void {
        GameSettleUp::GetInstance().stage = GameStage::LEVEL_GENERATE_STATUS;
    });

    beforeBattleMenus = Menu::create(checkPartnerMenuItem, openBattleLogMenuItem, nextLevelMenuItem, nullptr);
    beforeBattleMenus->alignItemsHorizontally();
    beforeBattleMenus->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    beforeBattleMenus->setPosition(GameDeclare::Size::screen.width / 2.0f, 15.0f);
    addChild(beforeBattleMenus);
    return;
}

void ConductScene::InitBattlingMenu()
{
    // 战斗中的菜单有，加速
    Label *accelerateBattleLabel = Label::createWithTTF("快进速度", GameDeclare::Font::FELT_TTF, 28);
    MenuItemLabel *accelerateBattleMenuItem = MenuItemLabel::create(accelerateBattleLabel, [this](Ref *ref) -> void {
        Director::getInstance()->getScheduler()->setTimeScale(2.0f);
        this->battlingMenus->getChildByTag(1)->setVisible(true);
        this->battlingMenus->getChildByTag(0)->setVisible(false);
    });

    Label *decelerateBattleLabel = Label::createWithTTF("正常速度", GameDeclare::Font::FELT_TTF, 28);
    MenuItemLabel *decelerateBattleMenuItem = MenuItemLabel::create(decelerateBattleLabel, [this](Ref *ref) -> void {
        // this->battleLayer->SetBattleSpeed(0.5f);
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);

        this->battlingMenus->getChildByTag(1)->setVisible(false);
        this->battlingMenus->getChildByTag(0)->setVisible(true);
    });
    decelerateBattleMenuItem->setVisible(false);

    battlingMenus = Menu::create();
    battlingMenus->alignItemsHorizontally();
    battlingMenus->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    battlingMenus->setPosition(GameDeclare::Size::screen.width / 2.0f, 15.0f);
    battlingMenus->addChild(accelerateBattleMenuItem, 1, 0);
    battlingMenus->addChild(decelerateBattleMenuItem, 1, 1);
    addChild(battlingMenus);
    return;
}

void ConductScene::update(float delta)
{
    /* 这里的控制流，采用状态机的模式 */
    if (GameSettleUp::GetInstance().stage == GameStage::BEFORE_BATTLE_STATUS) {
        beforeBattleMenus->setVisible(true);
        battlingMenus->setVisible(false);
    }
    if (GameSettleUp::GetInstance().stage == GameStage::LEVEL_GENERATE_STATUS) {
        LevelGenerator::Generate(GameSettleUp::GetInstance().currentArea);
        GameSettleUp::GetInstance().stage = GameStage::PLACE_ACTOR_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::PLACE_ACTOR_STATUS) {
        battleLayer->PlaceActor();
        GameSettleUp::GetInstance().stage = GameStage::BATTLING_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::BATTLING_STATUS) {
        beforeBattleMenus->setVisible(false);
        battlingMenus->setVisible(true);
        BattleCalc::GetInstance().Calc();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::PREPARE_ANIMATION_STATUS) {
        battleLayer->PlayBattleDetail();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::PLAY_ANIMATION_STATUS) {
        // nothing to do.
    }

    if (GameSettleUp::GetInstance().stage == GameStage::SETTLE_UP_STATUS) {
        GameSettleUp::GetInstance().SettleUp();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::GAMEOVER_STATUS) {
        GameSettleUp::GetInstance().UnInit();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::BEGIN_SELECT_STATUS) {
        GameSettleUp::GetInstance().stage = GameStage::WAIT_SELECT_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::WAIT_SELECT_STATUS) {
        // nothing to do.
    }
    
    if (GameSettleUp::GetInstance().stage == GameStage::END_SELECT_STATUS) {
        GameSettleUp::GetInstance().stage = GameStage::LEVEL_GENERATE_STATUS;
    }
    
    battleLayer->update(delta);
    return;
}
