
#include "ItemTextures.h"
#include <Directory.hpp>
#include <ResourceLoader.hpp>

using namespace godot;

ItemTextures::ItemTextures() {
}

ItemTextures::~ItemTextures() {
    // add your cleanup here
}

void ItemTextures::_register_methods() {
    register_method("_ready", &ItemTextures::_ready);
    register_method("_reload_textures", &ItemTextures::_reload_textures);
    register_method("_get_texture", &ItemTextures::_get_texture);
}

void ItemTextures::_ready(){
    _reload_textures();
}

void ItemTextures::_init() {
    
}

void ItemTextures::_reload_textures() {
    Directory *dir = Directory::_new();
    Array a = Array();

    if (dir->open("res://Assets/images") == Error::OK) {
        ResourceLoader* resourceLoader = ResourceLoader::get_singleton();

        dir->list_dir_begin (true, true);
        String text_type = ".png";
        String file = dir->get_next();
        while (!file.empty()) {
            if (!file.ends_with(text_type)) {
                file = dir->get_next();

                continue;
            }
            Ref<Texture> text = resourceLoader->load(dir->get_current_dir() + "/" + file);
            if (text.is_valid())
                a.append (text);
            file = dir->get_next();
        }

        textures = a;
    }
}

Ref<Texture> ItemTextures::_get_texture(int index) {
    if (textures.size() < index || index < 0) {
        printf ("Invalid Index. Max:%d, %d\n", textures.size(), index);
        return NULL;
    }
    else {
        return textures[index];
    }
}
