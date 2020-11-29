#ifndef INVITEM_H
#define INVITEM_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <TextureRect.hpp>
#include <StyleBoxFlat.hpp>
#include <Texture.hpp>
#include "InvSlot.h"

namespace godot {

    class InvItem : public TextureRect {
        GODOT_CLASS(InvItem, TextureRect)

    private:
        String itemName;
        InvSlot* itemSlot;
        Ref<Texture> texture;
    public:

        static void _register_methods();

        InvItem();
        ~InvItem();

        void _init();
        void _init(String _itemName, InvSlot* _itemSlot, Ref<Texture> _itemTexture); // our initializer called by Godot
        void _init(Ref<Texture> _itemTexture);
        void _ready();

        InvSlot* get_slot ();
        void set_slot (InvSlot* slot);

        String get_name ();

        bool isPicked = false;

        void pick_item();
        void put_item();
    };

}

#endif