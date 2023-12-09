#pragma once

#include "GameDeclare/DefineDeclare.h"
#include "ActorModel/ActorModel.h"
#include "BattleCalc/BattleCalc.h"
#include "..\LevelGenerator\GameArea.h"

enum class GameStage {
    PREPARE_BATTLE_STATUS = 0,
    ENTER_BATTLE_STATUS,
    PLACE_ACTOR_STATUS,
    BATTLING_STATUS,
    SETTLE_UP_STATUS,
    SELECT_STATUS,
    GAMEOVER_STATUS
};

class GameSettleUp {
    DECLARE_SINGLETON(GameSettleUp)

public:
    void Init(); // 首次进入游戏时候的调用
    void SettleUp(); // 开始结算
    void ShowSelect(); // 进入抉择状态
    void UnInit(); // 当游戏结束的时候，会调用这个函数，打印最终的游戏结束画面

    void CleanDeadActor();

    /* 对其他组件提供一些查询和获取方法 */
    Actor &GetActorById(int actorId);
    bool IsActorAlive(int actorId);


public:
    // 人物控制相关
    std::map<int, Actor> playerActors; // 玩家的人物组
    std::map<int, Actor> monsterActors; // 怪物的人物组

    // 关卡相关
    AreaName currentArea; // 当前游戏区域

    // 游戏推进相关
    GameStage stage;
    BattleDetail curBattleDetails;
};
