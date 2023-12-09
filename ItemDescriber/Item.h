#pragma once

#include <string>

namespace ItemName {
const std::string VOID_ITEM = "None Item";
const std::string A_ITEM = "A Item";
const std::string B_ITEM = "B Item";
const std::string C_ITEM = "C Item";

}

enum class ItemType {
    NONE,
    ADDITION
};

class Item { // 是物品描述器的具体实例，在游戏过程中都会控制Card这个类来使用
public:
    virtual void Apply() { return; }
    virtual void ApplyToActor(int actorId) { return; }

public:
    std::string name; // 物品名称
    ItemType type; // 物品类型
    std::string describe; // 物品描述
    std::string imagePath; // sprite资源路径
};

class VoidItem : public Item {
public:
    static Item *Create();
};

class AItem : public Item {
public:
    static Item *Create();
};

class BItem : public Item {
public:
    static Item *Create();
};

class CItem : public Item {
public:
    static Item *Create();
};