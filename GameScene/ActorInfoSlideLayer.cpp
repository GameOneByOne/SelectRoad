#include "ActorInfoSlideLayer.h"

#include "GameDeclare/AnimDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

ActorInfoSlideLayer *ActorInfoSlideLayer::InitLayer()
{
    auto pRet = new (std::nothrow) ActorInfoSlideLayer();
    if (pRet && pRet->Init()) {
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

    InitConstValue();

    // 初始化滑动页面
    scrollView = ui::ScrollView::create();
    scrollView->setContentSize({layerWidth, layerHeight});
    scrollView->setBounceEnabled(true);
    addChild(scrollView);
    
    // 初始化每个角色的详细信息
    maxOffset = layerHeight;
    for (const auto &actor : GameSettleUp::GetInstance().playerActors) {
        DrawNode *infoNode = DrawNode::create();
        infoNode->drawRect({10.0f, maxOffset - 200.0f}, {layerWidth - 10.0f, maxOffset - 10.0f}, Color4F::BLUE);
        infoNode->setAnchorPoint({0.0f, 0.0f});
        infoNode->setPosition({0.0f, 0.0f});
        maxOffset -= 230.0f;
        scrollView->addChild(infoNode, 30);
    }
    curOffset = 0.0f;
    
    // 初始化主边界框
    DrawNode *boundNode = DrawNode::create();
    boundNode->drawRect({0.0f, 0.0f}, {layerWidth, layerHeight}, Color4F::RED);
    boundNode->setAnchorPoint({0.0f, 0.0f});
    boundNode->setPosition({0.0f, 0.0f});
    this->addChild(boundNode, 20);
    InitMouseListener();

    return true;
}

void ActorInfoSlideLayer::InitConstValue()
{
    layerWidth = GameDeclare::Size::screen.width / 3.0f;
    layerHeight = GameDeclare::Size::screen.height / 5.0f * 4.0f;
    setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    return;
}

void ActorInfoSlideLayer::InitMouseListener()
{
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseScroll = [this](Event *event) -> void {
        const float span = 50.0f;
        float scrollY = ((EventMouse*)event)->getScrollY();
        curOffset = MAX(MIN(0, curOffset - span * scrollY), maxOffset);
        this->scrollView->setInnerContainerPosition({0.0f, -1 * curOffset});
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    return;
}

void ActorInfoSlideLayer::ToggleShow()
{
    isShow = !isShow;
    stopAllActions();
    if (isShow) {
        MoveTo *moveInAnim = MoveTo::create(0.25f, {slideX, slideY});
        runAction(moveInAnim);
    } else {
        MoveTo *moveOffAnim = MoveTo::create(0.25f, {-1 * layerWidth, slideY});
        runAction(moveOffAnim);
    }
    return;
}

void ActorInfoSlideLayer::SetSlidePosition(const cocos2d::Vec2 &pos)
{
    slideX = pos.x;
    slideY = pos.y;
    setPosition(-1 * layerWidth, slideY);
    return;
}

void ActorInfoSlideLayer::update(float delta)
{
    return;
}
