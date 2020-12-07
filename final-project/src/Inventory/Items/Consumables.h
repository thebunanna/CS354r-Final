#ifndef Consumables_H
#define Consumables_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <TextureRect.hpp>
#include <StyleBoxFlat.hpp>
#include <Texture.hpp>
#include "InvItem.h"

namespace godot {

    class Consumables : public InvItem {
        GODOT_CLASS(Consumables, InvItem)

    private:
        
    public:

        static void _register_methods();

        Consumables();
        ~Consumables();

        void _init();
        void _init(String _itemName, InvSlot* _itemSlot, int _itemTexture, ItemType _type); 

        void _ready();

        bool interact() override;
    };

}

#endif