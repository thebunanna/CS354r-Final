#include "Player.h"
#include "Map.h"
#include "Enemy.h"

#include "Inventory/Inventory.h"
#include "Inventory/InvSlot.h"
#include "Inventory/Items/InvItem.h"
#include "Inventory/Items/Consumables.h"
#include "Inventory/ItemTextures.h"

#include "UI/HealthBar.h"

#include "Entities/Chest.h"
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

void register_blob();

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    register_blob ();
}

void register_blob () {
    godot::register_class<godot::Player>();
    godot::register_class<godot::Inventory>();
    godot::register_class<godot::InvSlot>();
    godot::register_class<godot::ItemTextures>();
    godot::register_class<godot::InvItem>();
    godot::register_class<godot::Consumables>();

    godot::register_class<godot::HealthBar>();

    godot::register_class<godot::Map>();
    godot::register_class<godot::Enemy>();

    godot::register_class<godot::Chest>();
}