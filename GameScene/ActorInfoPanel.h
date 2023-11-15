#pragma once

#include <cocos2d.h>

class ActorInfoPanel : public cocos2d::Layer {
public:
    static cocos2d::Layer *InitLayer();
    bool Init();
    void update(float delta) override;
    
private:
    void InitPanel();
    void InitHPInfo();
    void InitActorOtherInfo();
    void InitMouseListener();

private:
    cocos2d::Size panelSize; /* 当前面板的大小 */
    std::vector<cocos2d::Sprite *> HPDynamicSprites; // 用于管理血量条
    cocos2d::Sprite *HPValueRightEdge = nullptr; // 用于自动更新HP的右边框
    cocos2d::Sprite *HPLeftCircle = nullptr;
    cocos2d::Label *attackInfoLabel = nullptr;
    cocos2d::Label *defenseInfoLabel = nullptr;
    cocos2d::Label *coolnessInfoLabel = nullptr;
    cocos2d::Label *duckInfoLabel = nullptr;
    cocos2d::Label *luckInfoLabel = nullptr;
};
