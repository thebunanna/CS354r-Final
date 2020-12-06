#include "InvItem.h"
#include <ResourceLoader.hpp>
#include <Label.hpp>
#include "../ItemTextures.h"

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
void InvItem::_init(String _name, InvSlot* _itemSlot, int _itemTexture, ItemType _type) {
    data.type = _type;
    data.itemName = _name;
    itemSlot = _itemSlot;
    data.texture_num = _itemTexture;
    //set_texture(_itemTexture);
}

void InvItem::_init(Ref<Texture> _itemTexture) {
    set_texture(_itemTexture);
}

void InvItem::_ready(){
    ItemTextures* bank = Object::cast_to<ItemTextures> (get_node(NodePath("/root/TextureBank")));
    set_texture (bank->_get_texture(data.texture_num));
}

InvSlot* InvItem::get_slot() {
    return itemSlot;
}

void InvItem::set_slot(InvSlot* slot) {
    itemSlot = slot;
}

String InvItem::get_name() {
    return data.itemName;
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
    Godot::print("interacting!" + data.itemName);
    return true;
}

///Should be called from InvSlot only. type is inv slot type.
///Used to check for valid slots.
bool InvItem::check_type (ItemType type) {
    if (type == ItemType::None) return true;
    else if (this->data.type == type) return true;
    
    return false;

}