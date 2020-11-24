#include "Map.h"
#include <ResourceLoader.hpp>
#include <Ref.hpp>

using namespace godot;

void Map::_register_methods() {
    register_method("_process", &Map::_process);
    register_method("generate", &Map::generate);
}

Map::Map() {
}

Map::~Map() {
    // add your cleanup here
}

void Map::_init() {
    // initialize any variables here
    // Resource loader for tile set, then cast to tile set and call set_tileset on that

    //// NOT NEEDED (can be set in the editor)
    //ResourceLoader* rl = ResourceLoader::get_singleton();
    //Ref<TileSet> tset = rl->load("res://Set1.tres");
    //set_tileset(tset);
}

void Map::_ready() {
    //generate();
    flag = true;
}

void Map::generate() {
    // This is where we will do the procedural generation
    clear();
    int tile = 0;
    for (int y = -1; y < 11; ++y) {
        set_cell(-1, y, tile);
        set_cell(10, y, tile);
    }
    for (int x = 0; x < 11; ++x) {
        set_cell(x, -1, tile);
        set_cell(x, 10, tile);
    }
    update_dirty_quadrants();
}

void Map::_process(float delta) {
    //bool flag = true;
    if (flag) {
        generate();
        flag = false;
    }
}