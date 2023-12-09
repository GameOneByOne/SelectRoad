#include "Item.h"
#include "GameDeclare/DefineDeclare.h"
#include "GameDeclare/ImageDeclare.h"

Item *VoidItem::Create()
{
    Item *item = new (std::nothrow) VoidItem();
    item->name = ItemName::VOID_ITEM;
    item->type = ItemType::NONE;
    item->describe = "None";
    item->imagePath = "";
    return item;
}

Item *AItem::Create()
{
    Item *item = new (std::nothrow) AItem();
    item->name = ItemName::A_ITEM;
    item->type = ItemType::ADDITION;
    item->describe = "A  item...";
    item->imagePath = "";
    return item;
}

Item *BItem::Create()
{
    Item *item = new (std::nothrow) BItem();
    item->name = ItemName::B_ITEM;
    item->type = ItemType::ADDITION;
    item->describe = "B  item...";
    item->imagePath = "";
    return item;
}

Item *CItem::Create()
{
    Item *item = new (std::nothrow) CItem();
    item->name = ItemName::C_ITEM;
    item->type = ItemType::ADDITION;
    item->describe = "C  item...";
    item->imagePath = "";
    return item;
}
