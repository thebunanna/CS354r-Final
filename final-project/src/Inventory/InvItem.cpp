#include "InvItem.h"

#include <Label.hpp>
using namespace godot;

void InvItem::_register_methods() {
    register_method("_ready", &InvItem::_ready);

}

InvItem::InvItem() {
}

InvItem::~InvItem() {
    // add your cleanup here
}
void InvItem::_init() {
    
}
// void InvItem::_init(String _name, InvSlot* _itemSlot, Ref<Texture> _itemTexture) {
//     itemName = _name;
//     itemSlot = _itemSlot;
//     set_texture(_itemTexture);
// }

void InvItem::_init(Ref<Texture> _itemTexture) {
    set_texture(_itemTexture);

}

void InvItem::_ready(){

}

InvSlot* InvItem::get_slot() {
    return itemSlot;
}

void InvItem::set_slot(InvSlot* slot) {
    //itemSlot = slot;
}

String InvItem::get_name() {
    return itemName;
}