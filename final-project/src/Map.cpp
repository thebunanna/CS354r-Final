#include "Map.h"

using namespace godot;

void Map::_register_methods() {
    register_method("_process", &Map::_process);
}

Map::Map() {
}

Map::~Map() {
    // add your cleanup here
}

void Map::_init() {
    // initialize any variables here
}

void Map::_ready() {

}

void Map::_process(float delta) {

}