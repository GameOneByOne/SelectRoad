#pragma once

#include "GameDeclare/DefineDeclare.h"
#include "ActorModel/ActorModel.h"
#include "BattleCalc/BattleCalc.h"
#include "..\LevelGenerator\GameArea.h"

enum class GameStage {
    LEVEL_GENERATE_STATUS,
    PLACE_ACTOR_STATUS,
    BATTLE_STATUS,
    PREPARE_ANIMATION_STATUS,
    PLAY_ANIMATION_STATUS,
    SETTLE_UP_STATUS,
    BEGIN_SELECT_STATUS,
    WAIT_SELECT_STATUS,
    END_SELECT_STATUS,
    GAMEOVER_STATUS
};

class GameSettleUp {
    DECLARE_SINGLETON(GameSettleUp)

public:
    void Init(); // 首次进入游戏时候的调用
    void SettleUp(); // 开始结算
    void ShowSelect(); // 进入抉择状态
    void UnInit(); // 当游戏结束的时候，会调用这个函数，打印最终的游戏结束画面

    /* 对其他组件提供一些查询和获取方法 */
    Actor &GetActorById(int actorId);

public:
    // 人物控制相关
    std::map<int, Actor> playerActors; // 玩家的人物组
    std::map<int, Actor> monsterActors; // 怪物的人物组

    // 关卡相关
    AreaName currentArea; // 当前游戏区域
    std::vector<Card> dropCards; // 当前关卡结束后，应该掉落的卡牌

    // 游戏推进相关
    GameStage stage;
    BattleDetail curBattleDetails;
};
