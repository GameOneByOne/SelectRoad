#include "BattleLogLayer.h"



#include "ActorInfoSlideLayer.h"

#include "GameDeclare/AnimDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameUtils/GameUtils.h"

USING_NS_CC;

BattleLogLayer *BattleLogLayer::InitLayer()
{
    auto pRet = new (std::nothrow) BattleLogLayer();
    if (pRet && pRet->Init()) {
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool BattleLogLayer::Init()
{
    if (!Layer::init()) {
        return false;
    }

    InitConstValue();

    // 初始化滑动页面
    scrollView = ui::ScrollView::create();
    scrollView->setContentSize({layerWidth, layerHeight});
    scrollView->setBounceEnabled(true);
    scrollView->setBackGroundColor(Color3B::BLACK);
    scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    addChild(scrollView);

    
    
    // 初始化主边界框
    DrawNode *boundNode = DrawNode::create();
    boundNode->drawRect({0.0f, 0.0f}, {layerWidth, layerHeight}, Color4F::RED);
    boundNode->setAnchorPoint({0.0f, 0.0f});
    boundNode->setPosition({0.0f, 0.0f});
    this->addChild(boundNode, 20);
    InitMouseListener();
    setContentSize({layerWidth, layerHeight});
    setColor(Color3B::BLACK);
    return true;
}

void BattleLogLayer::InitConstValue()
{
    layerWidth = GameDeclare::Size::screen.width / 3.0f - 20.0f;
    layerHeight = GameDeclare::Size::screen.height / 3.0f;
    setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    return;
}

void BattleLogLayer::InitMouseListener()
{
    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseScroll = [this](Event *event) -> void {
        const float span = 2.0f;
        float scrollY = ((EventMouse*)event)->getScrollY();
        curOffset = MAX(MIN(0, curOffset - span * scrollY), maxOffset);
        this->scrollView->setInnerContainerPosition({0.0f, -1 * curOffset});
        log("???????????????????  curOffset=%f   maxOffset=%f", curOffset * -1, maxOffset);
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    return;
}

void BattleLogLayer::InitLogContent()
{
    scrollView->removeAllChildrenWithCleanup(true);
    if (isShow) {
        ui::Text *logContent = ui::Text::create(battleLog, GameDeclare::Font::FELT_TTF, 12);
        logContent->setPosition({0.0f, layerHeight});
        logContent->setAnchorPoint(GameDeclare::Position::LEFT_UP);
        scrollView->addChild(logContent);
    }

    return;
}

void BattleLogLayer::ToggleShow()
{
    isShow = !isShow;
    stopAllActions();
    if (isShow) {
        MoveTo *moveInAnim = MoveTo::create(0.25f, {slideX, slideY});
        runAction(moveInAnim);
    } else {
        MoveTo *moveOffAnim = MoveTo::create(0.25f, {slideX, -1 * layerHeight - 5.0f});
        runAction(moveOffAnim);
    }
    
    InitLogContent();
    return;
}

void BattleLogLayer::AddLog(const std::string &log)
{
    battleLog += log;
    battleLog += "\n";
    maxOffset -= 12;
    if (isShow) {
        InitLogContent();
    }

    return;
}

void BattleLogLayer::SetSlidePosition(const cocos2d::Vec2 &pos)
{
    slideX = pos.x;
    slideY = pos.y;
    setPosition(slideX, -1 * layerHeight - 5.0f);
    return;
}
