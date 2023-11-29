#include "ActorInfoSlideLayer.h"

#include "GameDeclare/AnimDeclare.h"
#include "GameDeclare/SizeDeclare.h"

USING_NS_CC;

ActorInfoSlideLayer *ActorInfoSlideLayer::InitLayer()
{
    auto pRet = new (std::nothrow) ActorInfoSlideLayer();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ActorInfoSlideLayer::Init()
{
    if (!Layer::init()) {
        return false;
    }
    
    drawer = DrawNode::create(3.0f);
    BeginDrawActorInfoPanel();
    addChild(drawer);
    return true;
}

void ActorInfoSlideLayer::BeginDrawActorInfoPanel()
{
    // 画主框
    float rectHeight = GameDeclare::Size::screen.height / 12.0f * 11.0f; 
    float rectWidth = GameDeclare::Size::screen.width / 5.0f * 2.0f;
    drawer->drawRect({20.0f, 20.0f}, {rectWidth, rectHeight}, Color4F::RED);
    return;
}

