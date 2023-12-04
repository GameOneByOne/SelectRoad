#include "GameUtils.h"

USING_NS_CC;

namespace GameUtils {
std::string FormatIndex(int index, int length)
{
    std::string indexStr = std::to_string(index);
    while (indexStr.length() < length) {
        indexStr = "0" + indexStr;
    }
    return indexStr;
}

int GetRandomFromRange(const std::pair<int, int> &range)
{
    return (random() % (range.second - range.first)) + range.first;
}

float GetRandomFromRangeF(const std::pair<float, float> &range)
{
    return (random() % (int)(range.second - range.first)) + range.first;
}

Animate *GetAnimate(GameDeclare::Anim::AnimInfo animInfo, float delay, unsigned int loops)
{
    SpriteFrame *frame = nullptr;
    Vector<SpriteFrame *> frameVec;
    for (int i = 0; i < animInfo.animNum; ++i) {
        frame = SpriteFrame::create((animInfo.prefixPath + FormatIndex(i) + animInfo.suffixPath), animInfo.rect);
        frameVec.pushBack(frame);
    }

    Animation *ani = Animation::createWithSpriteFrames(frameVec, delay, loops);
    return Animate::create(ani);
}

cocos2d::Sprite *GetAnimateFrame(GameDeclare::Anim::AnimInfo animInfo, int index)
{
    Sprite *sprite = Sprite::create(animInfo.prefixPath + FormatIndex(index)+ animInfo.suffixPath);
    return sprite;
}
}
