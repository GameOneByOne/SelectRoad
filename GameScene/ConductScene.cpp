#include "ConductScene.h"
#include <string>

#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
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
    addChild(battleLayer, 10);

    scheduleUpdate();
    return true;
}

void ConductScene::update(float delta)
{
    /* 这里的控制流，采用状态机的模式 */
    if (GameSettleUp::GetInstance().stage == GameStage::LEVEL_GENERATE_STATUS) {
        LevelGenerator::Generate(GameSettleUp::GetInstance().currentArea);
        GameSettleUp::GetInstance().stage = GameStage::PLACE_ACTOR_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::PLACE_ACTOR_STATUS) {
        battleLayer->PlaceActor();
        GameSettleUp::GetInstance().stage = GameStage::BATTLE_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::BATTLE_STATUS) {
        BattleCalc::GetInstance().Calc();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::ANIMATION_STATUS) {
        battleLayer->PlayBattleDetails();
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
    
    return;
}
