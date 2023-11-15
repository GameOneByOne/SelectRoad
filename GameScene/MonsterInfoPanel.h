#pragma once

#include <cocos2d.h>

class MonsterInfoPanel : public cocos2d::Layer {
public:
    static cocos2d::Layer *InitLayer();
    bool Init();
    void update(float delta) override;
    
private:
    void InitInfoPanel();

private:
    cocos2d::Sprite *panelBackground = nullptr; // 用于显示怪物信息面板的背景图
    cocos2d::Label *HPLabel = nullptr; // 用于显示怪物HP的标签
    cocos2d::Label *attackLabel = nullptr; // 用于显示怪物攻击力的标签
    cocos2d::Label *defenseLabel = nullptr; // 用于显示怪物防御力的标签
};
