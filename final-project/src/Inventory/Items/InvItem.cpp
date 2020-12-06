#include "InvItem.h"
#include <ResourceLoader.hpp>
#include <Label.hpp>
#include <RandomNumberGenerator.hpp>

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
    _init (ItemBase());
}
void InvItem::_init(String _name, InvSlot* _itemSlot, int _itemTexture, ItemType _type) {
    data.type = _type;
    data.itemName = _name;
    itemSlot = _itemSlot;
    data.texture_num = _itemTexture;
    //set_texture(_itemTexture);
}
void InvItem::_init(ItemBase ib) {
    data = ib;
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

ItemBase InvItem::generate_item () {
    static auto rng = RandomNumberGenerator::_new();
    static bool gen = true;
    if (gen) {
        rng->randomize();
        gen = false;
    }

    ItemBase ret;

    ret.itemName = "something";
    ret.type = (ItemType) rng->randi_range(0, (int) ItemType::None);
    
    ret.texture_num = rng->randi_range(0, 7);

    printf ("%d, %d\n", (int)ret.type, ret.texture_num);

    return ret;
}

ItemBase InvItem::save_data () {
    return this->data;
}