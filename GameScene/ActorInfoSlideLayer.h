#pragma once

#include <cocos2d.h>

class ActorInfoSlideLayer : public cocos2d::Layer {
public:
    static ActorInfoSlideLayer *InitLayer();
    bool Init();

private:
    void BeginDrawActorInfoPanel();

private:
    cocos2d::DrawNode *drawer = nullptr;
};
