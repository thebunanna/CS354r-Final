#ifndef INVENTORY_H
#define INVENTORY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Panel.hpp>
#include <InputEvent.hpp>

#include "Items/InvItem.h"
#include "InvSlot.h"

namespace godot {

    class Inventory : public Panel {
        GODOT_CLASS(Inventory, Panel)

    private:
        bool is_open;

        int max_slots;
        Array items;
        Array equiped_items;


        InvItem* heldItem = nullptr;
        
    public:
        static void _register_methods();

        Inventory();
        ~Inventory();

        void _init(); // our initializer called by Godot

        void _ready();

        void _input (InputEvent * event);

        int get_next_empty();

        void add_item (InvItem* item);

        void slot_gui_event (InputEvent* e, InvSlot* slot);

        void create_inventory();

        void create_player_slots();
    };

}

#endif