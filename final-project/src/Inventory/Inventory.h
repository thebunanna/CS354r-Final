#ifndef INVENTORY_H
#define INVENTORY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Panel.hpp>
#include <InputEvent.hpp>

#include "InvItem.h"
#include "InvSlot.h"

namespace godot {

    class Inventory : public Panel {
        GODOT_CLASS(Inventory, Panel)

    private:
        uint max_slots;
        Array items;

    public:
        static void _register_methods();

        Inventory();
        ~Inventory();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);

        void _input (InputEvent * event);

        int get_next_empty();

        void add_item (InvItem* item);
    };

}

#endif