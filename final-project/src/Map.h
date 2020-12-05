#ifndef MAP_H
#define MAP_H

#include <Godot.hpp>
#include <TileMap.hpp>
#include <Sprite.hpp>
#include "Enemy.h"
#include <TileSet.hpp>
#include <AStar2D.hpp>

namespace godot {

    class Map : public TileMap {
        GODOT_CLASS(Map, TileMap)

    private:
        bool flag;
        Vector2 map_size;

        Array obstacles;
        AStar2D* astar;

        int tile_size = 64;


        Array astar_add_walkable_cells(Array obs);
        void astar_connect_walkable_cells(Array points);
        int calculate_point_index(Vector2 point);
        bool is_outside_map_bounds(Vector2 point);
        
        


    public:
        static void _register_methods();

        bool is_cell_vacant(Vector2 position, Vector2 direction);
        Vector2 update_child_pos(Vector2 position, Vector2 direction);

        Vector2 get_hitstun_tile(Vector2 position, Vector2 direction);

        void attack(Vector2 position, Vector2 direction, float damage);

        enum{WALL, FLOOR};

        Map();
        ~Map();

        void _init(); // our initializer called by Godot

        void _ready();

        void generate();

        PoolVector2Array get_path(Vector2 start, Vector2 end);

        void _process(float delta);
    };

}

#endif