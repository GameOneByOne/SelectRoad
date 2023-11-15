#include "SelectPanel.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "GameDeclare/FontDeclare.h"

USING_NS_CC;

cocos2d::Layer *SelectPanel::InitLayer()
{
    auto pRet = new (std::nothrow) SelectPanel();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool SelectPanel::Init()
{
    if (!Layer::init()) {
        return false;
    }
    
    InitPanel();
    InitSelectInfo();
    InitSelectListener();
    return true;
}

void SelectPanel::InitPanel()
{
    /* 加载面板素材 */
    selectPanel = Sprite::create(GameDeclare::Image::infoPanelTwoImage.path);
    selectPanel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);

    /* 设置缩放 */
    selectPanel->setScale(GameDeclare::Size::screen.width / selectPanel->getContentSize().width / 2.5f);

    /* 设置位置 */
    selectPanel->setPosition(GameDeclare::Size::screen.width / 2.0f - selectPanel->getBoundingBox().size.width / 2.0f, GameDeclare::Size::screen.height / 3.0f);
    
    addChild(selectPanel);
    return;
}

void SelectPanel::InitSelectInfo()
{
    /* 读取该显示多少张可选择的卡牌 */
    size_t cardNum = GameSettleUp::GetInstance().dropCards.size();

    /* 分布好各个卡牌的位置 */
    float beginY = selectPanel->getPosition().y + selectPanel->getBoundingBox().size.height / 8.0f * 5.0f;  // 卡牌的起始Y位置
    for (size_t index = 0; index < cardNum; ++index) {
        float beginX = selectPanel->getPosition().x + selectPanel->getBoundingBox().size.width / (cardNum + 1.0f) * (index + 1.0f); // 卡牌的起始X位置
        /* 创建好卡牌的边框 */
        Sprite *card = Sprite::create(GameSettleUp::GetInstance().dropCards[index].imagePath);
        card->setAnchorPoint(GameDeclare::Position::CENTER);
        card->setScale(selectPanel->getBoundingBox().size.height / card->getBoundingBox().size.height / (cardNum + 1.0f));
        card->setPosition({beginX, beginY});

        /* 补充好卡牌的详情 */
        std::string cardDesc = GameSettleUp::GetInstance().dropCards[index].describe;
        Label *cardDescribe = Label::createWithTTF(cardDesc, GameDeclare::Font::FELT_TTF, 16);
        cardDescribe->setAnchorPoint(GameDeclare::Position::MIDDLE_UP);
        cardDescribe->setWidth(card->getBoundingBox().size.width);
        cardDescribe->setOverflow(Label::Overflow::RESIZE_HEIGHT);
        cardDescribe->setPosition({card->getPosition().x, card->getPosition().y - card->getBoundingBox().size.height / 2 - 5.0f});
        addChild(card);
        addChild(cardDescribe);
        cardSelects.push_back(card);
    }
}

void SelectPanel::InitSelectListener()
{
    /* 开启选择了哪张卡牌的监听 */
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(SelectPanel::OnMouseUp, this);

    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return;
}

void SelectPanel::OnMouseUp(EventMouse* event)
{
    Vec2 clickLoc = event->getLocationInView();
    for (size_t index = 0; index < cardSelects.size(); ++index) {
        Rect rect = cardSelects[index]->getBoundingBox();
        if (cardSelects[index]->getBoundingBox().containsPoint(clickLoc)) {
            GameSettleUp::GetInstance().playerActor.AddCard(GameSettleUp::GetInstance().dropCards[index]);
            cardSelects.clear();
            GameSettleUp::GetInstance().stage = GameStage::END_SELECT_STATUS;
        }
    }
    return;
}


