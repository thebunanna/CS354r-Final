#ifndef INVSLOT_H
#define INVSLOT_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Panel.hpp>
#include <StyleBoxFlat.hpp>

namespace godot {

    class InvSlot : public Panel {
        GODOT_CLASS(InvSlot, Panel)

    private:
        uint slot_num;
        String item;
        StyleBoxFlat* style;

    public:
        static void _register_methods();

        InvSlot();
        ~InvSlot();

        void _init();
        void _init(String _name); // our initializer called by Godot

        void _ready();
        void refreshColors();

        void on_mouse_enter();
        void on_mouse_exit();
    };

}

#endif