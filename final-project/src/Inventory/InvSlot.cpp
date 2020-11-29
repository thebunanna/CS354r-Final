#include "InvSlot.h"
#include "InvItem.h"

#include <SceneTree.hpp>
#include <Node.hpp>
#include <Label.hpp>
#include <Viewport.hpp>
using namespace godot;

void InvSlot::_register_methods() {
    register_method("_ready", &InvSlot::_ready);
    register_method("refreshColors", &InvSlot::refreshColors);
    register_method("on_mouse_enter", &InvSlot::on_mouse_enter);
    register_method("on_mouse_exit", &InvSlot::on_mouse_exit);

}

InvSlot::InvSlot() {
}

InvSlot::~InvSlot() {
    // add your cleanup here
}
void InvSlot::_init() {
    _init (0);
}
void InvSlot::_init(int num) {
    // initialize any variables here
    slot_num = num;
    set_custom_minimum_size(Vector2(34,34));
    item = NULL;
}

void InvSlot::_ready(){
    Label* temp = Label::_new();
    temp->set_text (String::num(slot_num));
    add_child (temp);

    style = StyleBoxFlat::_new();
    refreshColors ();
    set("custom_styles/panel", style);

    connect ("mouse_entered", this, "on_mouse_enter");
    connect ("mouse_exited", this, "on_mouse_exit");
}

void InvSlot::refreshColors() {
	// if item:
	// 	style.bg_color = Color(Global.RarityColor[item.rarity].background);
	// 	style.border_color = Color(Global.RarityColor[item.rarity].border);
	// else:
    //style->set_bg_color (Color(0x8B, 0x72, 0x58));
    style->set_border_color (Color(0, 0, 0));
    style->set_border_width_all(3);
    style->set_bg_color (Color(0.1,0.2,0.3));
}

void InvSlot::on_mouse_enter () {
    style->set_bg_color (Color (0.2, 0.2, 0.4));
}
void InvSlot::on_mouse_exit () {
    refreshColors ();
}

bool InvSlot::get_empty () {
    return item == NULL; 
}

void InvSlot::set_item(InvItem* newItem) {
    
    add_child(newItem);

	item = newItem;
    
	item->set_slot(this);

	refreshColors();
}
	
InvItem* InvSlot::pick_item () {
    if (item == nullptr) return nullptr;
    
    item->pick_item();
	remove_child(item);
    
	get_node(NodePath("/root/Main/Inventory"))->add_child(item);    
	refreshColors();

    InvItem* temp = item;
    item = nullptr;
    return temp;
}

bool InvSlot::put_item(InvItem* newItem) {
    if (item != nullptr) return false;
	item = newItem;
    item->set_slot (this);
    item->put_item();

    get_node(NodePath("/root/Main/Inventory"))->remove_child(item);
    add_child(newItem);

	refreshColors();

    return true;
}

bool InvSlot::remove_item () {
    if (item == nullptr) return false;
    remove_child(item);
	item = nullptr;
	refreshColors();
    return true;
}