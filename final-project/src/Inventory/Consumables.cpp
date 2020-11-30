#include "Consumables.h"
#include <ResourceLoader.hpp>
#include <Label.hpp>
#include "../Player.h"
using namespace godot;

void Consumables::_register_methods() {
    register_method("_ready", &Consumables::_ready);
}

Consumables::Consumables() {
}

Consumables::~Consumables() {
    // add your cleanup here
}

void Consumables::_init() {
    InvItem::_init();
}

void Consumables::_init(String _name, InvSlot* _itemSlot, Ref<Texture> _itemTexture) {
    InvItem::_init(_name, _itemSlot, _itemTexture);
}


void Consumables::_ready() {

}

bool Consumables::interact() {
    Player* p = Object::cast_to<Player>(get_node(NodePath("/root/Main/Player")));
    p->modify_health(30);

    if (itemSlot != NULL) itemSlot->remove_item();
    else {
        printf ("null? \n");
    }

    return true;
}