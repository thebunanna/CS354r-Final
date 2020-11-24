#include "Inventory.h"
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
#include <ResourceLoader.hpp>


using namespace godot;

void Inventory::_register_methods() {
    register_method("_process", &Inventory::_process);
    register_method("_ready", &Inventory::_ready);
    register_method("_input", &Inventory::_input);
    register_method("get_next_empty", &Inventory::get_next_empty);
}

Inventory::Inventory() {
}

Inventory::~Inventory() {
    // add your cleanup here
}

void Inventory::_init() {
    max_slots = 20;
    // initialize any variables here
}

void Inventory::_ready(){
    items = Array();
    items.resize(max_slots);
    
    Node* gui_slots = get_node(NodePath("SlotContainer/InventorySlots"));
    
    for (int i = 0; i < max_slots; i++) {

        InvSlot* it = InvSlot::_new();
        it->_init(i);

        items[i] = it;
        gui_slots->add_child(it);
    }

    //ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    //Ref<Texture> text = resourceLoader->load("res://images/W_Sword001.png");

    //InvItem* item = InvItem::_new();
    //item->_init();
    // item->_init(text);
    //add_item (item);

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

int Inventory::get_next_empty () {
    for (int i = 0; i < max_slots; i++) {
        InvSlot* it = Object::cast_to<InvSlot>(items[i]);
        if (it->get_empty())
            return i;
    }
    return -1;
}

void Inventory::add_item (InvItem* item) {
    int slot_idx = get_next_empty ();
    if (slot_idx != -1) {
        InvSlot* it = Object::cast_to<InvSlot>(items[slot_idx]);
        it->set_item(item);
    }
}