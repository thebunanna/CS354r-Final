#include "Inventory.h"
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
#include <ResourceLoader.hpp>
#include <Viewport.hpp>
#include "Consumables.h"

using namespace godot;


void Inventory::_register_methods() {
    register_method("_process", &Inventory::_process);
    register_method("_ready", &Inventory::_ready);
    register_method("_input", &Inventory::_input);
    register_method("get_next_empty", &Inventory::get_next_empty);
    register_method("slot_gui_event", &Inventory::slot_gui_event);
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
        Array temp = Array();
        temp.append(it);

        it->connect("gui_input", this, "slot_gui_event", temp);
    }

    //test code remove later.
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    Ref<Texture> text = resourceLoader->load("res://Assets/images/W_Sword001.png");
    
    InvItem* test = InvItem::_new();
    test->_init("sword", nullptr, text);

    add_item(test);

    InvItem* test2 = InvItem::_new();
    test2->_init("sword", nullptr, text);

    add_item(test2);

    Ref<Texture> text2 = resourceLoader->load("res://Assets/images/Ac_Ring05.png");

    Consumables* test3 = Consumables::_new();
    test3->_init("sword", nullptr, text2);
    
    add_item(test3);

    //Object::cast_to<InvItem>(items[0])->set_item()
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
    if (heldItem && heldItem->isPicked) { 
        heldItem->set_position(get_global_mouse_position());
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

void Inventory::slot_gui_event (InputEvent* e, InvSlot* slot) {
    if (e->is_action_pressed("ui_inventory_select")) {
        if (heldItem == nullptr) {
            InvItem* item = slot->pick_item();
            if (item != nullptr)
            {
                heldItem = item;
                heldItem->set_position(get_global_mouse_position());
            }
        }
        else {
            if (slot->put_item(heldItem)) {
                heldItem = nullptr;
            }
        }
    }
    else if (e->is_action_pressed("ui_inventory_use")) {
        InvItem* item = slot->get_item();
        if (item != nullptr)
        {
            item->interact();
        }

    }
}
