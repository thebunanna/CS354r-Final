#ifndef INVSLOT_H
#define INVSLOT_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Panel.hpp>
#include <StyleBoxFlat.hpp>


namespace godot {
    class InvItem;

    class InvSlot : public Panel {
        GODOT_CLASS(InvSlot, Panel)

    private:
        int slot_num;
        InvItem* item;
        StyleBoxFlat* style;
    public:
        static void _register_methods();

        InvSlot();
        ~InvSlot();

        void _init();
        void _init(int num); // our initializer called by Godot

        void _ready();
        void refreshColors();

        void on_mouse_enter();
        void on_mouse_exit();

        bool get_empty();

        void set_item(InvItem* newItem);
        InvItem* pick_item ();
        InvItem* get_item ();
        bool put_item(InvItem* newItem);
        bool remove_item ();
    };

}

#endif