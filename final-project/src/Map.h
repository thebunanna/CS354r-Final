#ifndef MAP_H
#define MAP_H

#include <Godot.hpp>
#include <TileMap.hpp>

namespace godot {

    class Map : public TileMap {
        GODOT_CLASS(Map, TileMap)

    private:
    public:
        static void _register_methods();

        Map();
        ~Map();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);
    };

}

#endif