#include "InvItem.h"
#include <ResourceLoader.hpp>
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
void InvItem::_init(String _name, InvSlot* _itemSlot, Ref<Texture> _itemTexture) {
    itemName = _name;
    itemSlot = _itemSlot;
    set_texture(_itemTexture);
}

void InvItem::_init(Ref<Texture> _itemTexture) {
    set_texture(_itemTexture);
}

void InvItem::_ready(){

}

InvSlot* InvItem::get_slot() {
    return itemSlot;
}

void InvItem::set_slot(InvSlot* slot) {
    itemSlot = slot;
}

String InvItem::get_name() {
    return itemName;
}

void InvItem::pick_item() {
    set_mouse_filter (Control::MOUSE_FILTER_IGNORE);
	isPicked = true;
}
	

void InvItem::put_item() {
    set_position(Vector2(0,0));
    set_mouse_filter (Control::MOUSE_FILTER_PASS);
	isPicked = false;
}
	
bool InvItem::interact() {
    Godot::print("interacting!" + itemName);
    return true;
}