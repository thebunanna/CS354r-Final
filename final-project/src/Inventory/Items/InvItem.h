#ifndef INVITEM_H
#define INVITEM_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <TextureRect.hpp>
#include <StyleBoxFlat.hpp>
#include <Texture.hpp>
#include "../ItemTypes.h"
#include "../InvSlot.h"

namespace godot {

    class InvSlot;

    struct ItemBase {
        String itemName;
        int texture_num;
        ItemType type;
    };

    class InvItem : public TextureRect {
        GODOT_CLASS(InvItem, TextureRect)

    protected:
        struct ItemBase data;
        InvSlot* itemSlot;

    public:

        static void _register_methods();

        InvItem();
        ~InvItem();

        void _init(); // our initializer called by Godot
        void _init(String _itemName, InvSlot* _itemSlot, int _itemTexture, ItemType _type); 

        void _init(Ref<Texture> _itemTexture);

        void _ready();

        InvSlot* get_slot ();
        void set_slot (InvSlot* slot);

        String get_name ();

        bool isPicked = false;

        void pick_item();
        void put_item();

        bool check_type (ItemType type);

        virtual bool interact ();
    };

}

#endif