#include "ActorInfoSlideLayer.h"

#include "GameDeclare/AnimDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameUtils/GameUtils.h"

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
    scrollView->setBackGroundColor(Color3B::BLACK);
    scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    addChild(scrollView);
    
    InitActorInfo();
    
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

void ActorInfoSlideLayer::InitActorInfo()
{
    // 初始化每个角色的详细信息
    maxOffset = layerHeight - 210.0f;
    for (const auto &actor : GameSettleUp::GetInstance().playerActors) {
        const float rectWidth = layerWidth - 20.0f;
        const float rectHeight = 180.0f;

        DrawNode *infoNode = DrawNode::create();
        infoNode->drawRect({0.0f, 0.0f}, {rectWidth, rectHeight}, Color4F::BLUE);
        infoNode->setAnchorPoint({0.0f, 0.0f});
        infoNode->setPosition({10.0f, maxOffset});
    
        // 开始描绘每个角色的信息面板
        Sprite *spriteActor = GameUtils::GetAnimateFrame(actor.second.idleAnim, 0);
        spriteActor->setScale(0.2f);
        spriteActor->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
        spriteActor->setPosition({0.0f, 0.0f});
        infoNode->addChild(spriteActor);

        Label *HPLabel = Label::createWithTTF(StringUtils::format("生命值： %d", actor.second.HP), GameDeclare::Font::FELT_TTF, 28);
        Label *attackLabel = Label::createWithTTF(StringUtils::format("攻击力： %d", actor.second.attack), GameDeclare::Font::FELT_TTF, 28);
        Label *defenseLabel = Label::createWithTTF(StringUtils::format("防御力： %d", actor.second.defense), GameDeclare::Font::FELT_TTF, 28);
        HPLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
        attackLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
        defenseLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
        HPLabel->setPosition(150.0f, 60.0f);
        attackLabel->setPosition(150.0f, 40.0f);
        defenseLabel->setPosition(150.0f, 20.0f);
    
        infoNode->addChild(HPLabel);
        infoNode->addChild(attackLabel);
        infoNode->addChild(defenseLabel);
        
        maxOffset -= 210.0f;
        scrollView->addChild(infoNode, 30, 0);
    }
    curOffset = 0.0f;
    maxOffset += 180.0f;
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

    scrollView->removeAllChildrenWithCleanup(true);
    InitActorInfo();
    return;
}

void ActorInfoSlideLayer::SetSlidePosition(const cocos2d::Vec2 &pos)
{
    slideX = pos.x;
    slideY = pos.y;
    setPosition(-1 * layerWidth, slideY);
    return;
}
