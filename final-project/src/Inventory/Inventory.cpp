#include "Inventory.h"
#include "InvSlot.h"
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
using namespace godot;

void Inventory::_register_methods() {
    register_method("_process", &Inventory::_process);
    register_method("_ready", &Inventory::_ready);
    register_method("_input", &Inventory::_input);

}

Inventory::Inventory() {
}

Inventory::~Inventory() {
    // add your cleanup here
}

void Inventory::_init() {
    slots = 20;
    // initialize any variables here
}

void Inventory::_ready(){
    items = Array();
    items.resize(slots);
    
    Node* gui_slots = get_node(NodePath("SlotContainer/InventorySlots"));
    
    for (int i = 0; i < slots; i++) {

        InvSlot* it = InvSlot::_new();
        it->_init(String::num(i));
        items[i] = it;
        gui_slots->add_child(it);
    }
    
}

void Inventory::_process(float delta) {

}

void Inventory::_input (InputEvent *event) {
    if (event->is_action_pressed("ui_inventory")) {
        this->set_visible(true);
    }
    else if (event->is_action_pressed("ui_cancel")){
        this->set_visible(false);
        get_tree()->set_input_as_handled();
    }
    
}
