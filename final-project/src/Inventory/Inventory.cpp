#include "Inventory.h"
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
#include <ResourceLoader.hpp>
#include <Viewport.hpp>
#include "Items/Consumables.h"

using namespace godot;


void Inventory::_register_methods() {
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
    max_slots = 24;
    // initialize any variables here
}

void Inventory::_ready(){

    is_open = false;
    this->set_visible(false);

    create_inventory ();
    
    create_player_slots ();
    

    //test code remove later.
    
    InvItem* test = InvItem::_new();
    test->_init("sword", nullptr, 3, ItemType::Weapon);

    add_item(test);

    InvItem* test2 = InvItem::_new();
    test2->_init("armour", nullptr, 0, ItemType::Armour);

    add_item(test2);


    Consumables* test3 = Consumables::_new();
    test3->_init("not really a sword", nullptr, 1, ItemType::Other);
    
    add_item(test3);

    //Object::cast_to<InvItem>(items[0])->set_item()
}

void Inventory::create_inventory() {
    items = Array();
    items.resize(max_slots);
    
    Node* gui_slots = get_node(NodePath("VBOX/MainInventory/InventorySlots"));
    
    for (int i = 0; i < max_slots; i++) {

        InvSlot* it = InvSlot::_new();
        it->_init(i, ItemType::None);
        items[i] = it;

        gui_slots->add_child(it);
        Array temp = Array();
        temp.append(it);

        it->connect("gui_input", this, "slot_gui_event", temp);
    }
}
void Inventory::create_player_slots() {
    Node* gui_slots = get_node(NodePath("VBOX/Equipment"));

    equiped_items = Array();
    equiped_items.resize(6);

    ItemType eqtype[] = {
        ItemType::Weapon, 
        ItemType::Armour,
        ItemType::Armour,
        ItemType::Armour,
        ItemType::Armour,
        ItemType::Other,
    };

    for (int i = 0; i < 6; i++) {
        InvSlot* it = InvSlot::_new();
        it->_init(i, eqtype[i]);
        equiped_items[i] = it;

        gui_slots->add_child(it);
        Array temp = Array();
        temp.append(it);

        it->connect("gui_input", this, "slot_gui_event", temp);
    }
    
}

void Inventory::_input (InputEvent *event) {
    if (event->is_action_pressed("ui_inventory")) {
        is_open = !is_open;
        this->set_visible(is_open);
        get_tree()->set_pause(is_open);
        get_tree()->set_input_as_handled();

    }
    else if (event->is_action_pressed("ui_cancel")){
        this->set_visible(false);
        get_tree()->set_pause(false);
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
