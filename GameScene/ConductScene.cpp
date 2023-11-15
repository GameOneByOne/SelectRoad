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
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ConductScene::Init()
{
    if (!Scene::init()) {
        return false;
    }
    
    /* 初始化界面及游戏结算期， 之后就会进入update函数，开始主逻辑循环 */
    GameSettleUp::GetInstance().Init();
    LevelGenerator::GetInstance().Generate();

    battlePanel = BattlePanel::InitLayer();
    areaInfoPanel = AreaInfoPanel::InitLayer();
    actorInfoPanel = ActorInfoPanel::InitLayer();
    monsterInfoPanel = MonsterInfoPanel::InitLayer();
    InitConductLogPanel();

    addChild(battlePanel, 10);
    addChild(areaInfoPanel);
    addChild(actorInfoPanel);
    addChild(monsterInfoPanel);
    
    scheduleUpdate();
    return true;
}

void ConductScene::InitConductLogPanel()
{
    conductLogPanel = Sprite::create(GameDeclare::Image::infoPanelImage.path, GameDeclare::Image::infoPanelImage.rect);
    conductLogPanel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    float scaleX = GameDeclare::Size::screen.width / conductLogPanel->getBoundingBox().size.width / 3.0f;
    float scaleY =  GameDeclare::Size::screen.height / conductLogPanel->getBoundingBox().size.height / 3.0f;
    conductLogPanel->setPosition({GameDeclare::Size::screen.width * 0.33f, 0.0f});
    conductLogPanel->setScale(scaleX, scaleY);
    addChild(conductLogPanel);
    return;
}

void ConductScene::update(float delta)
{
    /* 这里的控制流，采用状态机的模式 */
    if (GameSettleUp::GetInstance().stage == GameStage::LEVEL_GENERATE_STATUS) {
        LevelGenerator::GetInstance().Generate();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::BATTLE_STATUS) {
        BattleCalc::GetInstance().Calc();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::ANIMATION_STATUS) {
        // nothing to do.
    }

    if (GameSettleUp::GetInstance().stage == GameStage::SETTLE_UP_STATUS) {
        GameSettleUp::GetInstance().SettleUp();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::GAMEOVER_STATUS) {
        GameSettleUp::GetInstance().UnInit();
    }

    if (GameSettleUp::GetInstance().stage == GameStage::BEGIN_SELECT_STATUS) {
        selectInfoPanel = SelectPanel::InitLayer();
        addChild(selectInfoPanel);
        GameSettleUp::GetInstance().stage = GameStage::WAIT_SELECT_STATUS;
    }

    if (GameSettleUp::GetInstance().stage == GameStage::WAIT_SELECT_STATUS) {
        // nothing to do.
    }
    
    if (GameSettleUp::GetInstance().stage == GameStage::END_SELECT_STATUS) {
        removeChild(selectInfoPanel);
        selectInfoPanel = nullptr;
        GameSettleUp::GetInstance().stage = GameStage::LEVEL_GENERATE_STATUS;
    }
    
    battlePanel->update(delta);
    areaInfoPanel->update(delta);
    actorInfoPanel->update(delta);
    monsterInfoPanel->update(delta);
    return;
}
