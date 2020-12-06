#ifndef CHEST_H
#define CHEST_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include "../Inventory/Items/InvItem.h"

namespace godot {

    class Chest : public Area2D {
        GODOT_CLASS(Chest, Area2D)

    private:
        ItemBase inv[10];
    public:

        static void _register_methods();

        Chest();
        ~Chest();

        void _init();

        void _ready();

        void _exit_tree();

        ItemBase* get_inv ();

        void set_slot (ItemBase, int);

        void remove_if_empty ();

    };

}

#endif