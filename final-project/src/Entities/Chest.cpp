#include "Chest.h"
#include <ResourceLoader.hpp>
#include <Label.hpp>
#include <RandomNumberGenerator.hpp>
using namespace godot;

void Chest::_register_methods() {
    register_method("_ready", &Chest::_ready);
    register_method("_exit_tree", &Chest::_exit_tree);

}

Chest::Chest() {
}

Chest::~Chest() {
    // add your cleanup here
}

void Chest::_init() {

}

void Chest::_ready() {
    auto rng = RandomNumberGenerator::_new();
    rng->randomize();
    int size = rng->randi_range (0, 10);
    printf ("Generating %d items\n", size);

    for (int i = 0; i < size; i++) {
        inv[i] = InvItem::generate_item();
    }
    for (int i = size; i < 10; i++) {
        inv[i] = ItemBase();
    }
}

void Chest::_exit_tree () {

}

ItemBase* Chest::get_inv () {
    return inv;
};

void Chest::set_slot (ItemBase data, int index) {
    inv[index] = data;
}

void Chest::remove_if_empty () {
    bool found = true;
    for (int i = 0; i < 10; i++) {
        if (! (inv[i] == ItemBase())) {
            found = false;
        }
    }
    
    if (found) {
        queue_free();
    }
}