#include "Map.h"
#include <ResourceLoader.hpp>
#include <Ref.hpp>
#include <PoolArrays.hpp>
#include <RandomNumberGenerator.hpp>

using namespace godot;

void Map::_register_methods() {
    register_method("_process", &Map::_process);
    register_method("_ready", &Map::_ready);

    register_method("generate", &Map::generate);
    register_method("get_path", &Map::get_path);
    register_method("is_cell_vacant", &Map::is_cell_vacant);
    register_method("update_child_pos", &Map::update_child_pos);
    register_method("get_hitstun_tile", &Map::get_hitstun_tile);
    register_method("attack", &Map::attack);
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

    astar = AStar2D::_new();
}

void Map::_ready() {
    //generate();
    flag = true;

    
}

void Map::generate() {
    // This is where we will do the procedural generation
    clear();

    int min_x = 20;
    int max_x = 30;
    int min_y = 20;
    int max_y = 30;

    int min_rooms = 10;
    int max_rooms = 20;

    int room_min_x = 5;
    int room_max_x = 10;
    int room_min_y = 5;
    int room_max_y = 10;

    RandomNumberGenerator* rng = RandomNumberGenerator::_new();
    rng->randomize();

    int map_x = rng->randi_range(min_x, max_x);
    int map_y = rng->randi_range(min_y, max_y);
    int num_rooms = rng->randi_range(min_rooms, max_rooms);

    /*Godot::print("this is a thing that i want to print");
    Godot::print("X: " + std::to_string(map_x));
    Godot::print("Y: ");
    Godot::print("i should have printed the thing");*/

    //map_size = Vector2(12, 12);
    map_size = Vector2(map_x, map_y);

    /* Tileset */
    int wall = 0;
    int floor = 1;

    /* Fill with walls */
    for (int x = 0; x < map_size.x; ++x) {
        for (int y = 0; y < map_size.y; ++y) {
            set_cell(x, y, wall);
        }
    }

    for (int r = 0; r < num_rooms; ++r) {
        int r_x = rng->randi_range(room_min_x, room_max_x);
        int r_y = rng->randi_range(room_min_y, room_max_y);

        int room_pos_x = rng->randi_range(1, map_size.x - r_x - 1);
        int room_pos_y = rng->randi_range(1, map_size.y - r_y - 1);
        for (int rx = room_pos_x; rx < room_pos_x + r_x; ++rx) {
            for (int ry = room_pos_y; ry < room_pos_y + r_y; ++ry) {
                set_cell(rx, ry, floor);
            }
        }
    }


    set_cell(1, 1, 1);

    ///* Y outer walls */
    //for (int y = 0; y < map_size.y; ++y) {
    //    set_cell(0, y, tile);
    //    set_cell(map_size.x-1, y, tile);
    //}

    ///* X outer walls */
    //for (int x = 0; x < map_size.x; ++x) {
    //    set_cell(x, 0, tile);
    //    set_cell(x, map_size.y-1, tile);
    //}

    ///* Inner floor */
    //for(int x = 1; x < map_size.x - 1; x++){
    //    for(int y = 1; y < map_size.y - 1; y++){
    //        set_cell(x, y, 1);
    //    }
    //}

    update_dirty_quadrants();
}

void Map::_process(float delta) {

    //bool flag = true;
    if (flag) {
        Godot::print ("I should be genereating");

        generate();
        flag = false;

        obstacles = get_used_cells_by_id(0);
        Array walkable_cells = astar_add_walkable_cells(obstacles);
        astar_connect_walkable_cells(walkable_cells);
    }
}


Array Map::astar_add_walkable_cells(Array obs){
    
    Array points_arr;

    for(int y=0; y < map_size.y; y++){
        for(int x=0; x < map_size.x; x++){
            Vector2 point = Vector2(x, y);
            if(obs.has(point))
                continue;

            points_arr.append(point);

            int point_index = calculate_point_index(point);

            astar->add_point(point_index, point);
        }
    }

    return points_arr;
}

void Map::astar_connect_walkable_cells(Array points){
    for(int i=0; i<points.size(); i++){

        Vector2 point = points[i];
        int point_index = calculate_point_index(point);

        PoolVector2Array relative_points;
        relative_points.append(Vector2(point.x + 1, point.y));
        relative_points.append(Vector2(point.x - 1, point.y));
        relative_points.append(Vector2(point.x, point.y + 1));
        relative_points.append(Vector2(point.x, point.y - 1));

        for(int j=0; j<relative_points.size(); j++){
            Vector2 rel_point = relative_points[j];
            int rel_point_index = calculate_point_index(rel_point);

            if(is_outside_map_bounds(rel_point))
                continue;

            if(!astar->has_point(rel_point_index))
                continue;

            //false means its a one-way connection, since we loop through all points it's ok
            astar->connect_points(point_index, rel_point_index, false);
        }
    }
}

int Map::calculate_point_index(Vector2 point){
    return point.x + map_size.x * point.y;
}

bool Map::is_outside_map_bounds(Vector2 point){
    return point.x < 0 || point.y < 0 || point.x >= map_size.x || point.y >= map_size.y;
}

PoolVector2Array Map::get_path(Vector2 start, Vector2 end){
    start = start / tile_size;
    end = end / tile_size;

    int start_index = calculate_point_index(start);
    int end_index = calculate_point_index(end);
   
    return astar->get_point_path(start_index, end_index);
}

bool Map::is_cell_vacant(Vector2 position, Vector2 direction){
    
    Vector2 target_tile = world_to_map(position) + direction;
    
    if (target_tile.x < map_size.x && target_tile.x >= 0) {
        if(target_tile.y < map_size.y && target_tile.y >= 0){
            return get_cell(target_tile.x, target_tile.y) == FLOOR;
        }
    }

    return false;
}
Vector2 Map::update_child_pos(Vector2 position, Vector2 direction){

    Vector2 this_tile = world_to_map(position);
    Vector2 new_tile = this_tile + direction;

    Vector2 new_pos = map_to_world(new_tile);
    return new_pos;
}

Vector2 Map::get_hitstun_tile(Vector2 position, Vector2 direction){
    
    Vector2 curr_tile = world_to_map(position);

    Vector2 res_tile = curr_tile + (direction * 2);

    if(is_cell_vacant(map_to_world(res_tile), Vector2())){
        return map_to_world(res_tile);
    }

    res_tile = curr_tile + direction;

    if(is_cell_vacant(map_to_world(res_tile), Vector2())){
        return map_to_world(res_tile);
    }

    return map_to_world(curr_tile);
}

void Map::attack(Vector2 position, Vector2 direction, float damage){

    Vector2 attack_tile = world_to_map(position.snapped(Vector2(tile_size, tile_size))) + direction;

    Node* enemy_node = static_cast<godot::Node*>(get_node("/root/Main/Enemies"));
    Array enemies = enemy_node->get_children();

    if(enemies.size() != 0){
        for(int i=0; i<enemies.size(); i++){
            Enemy* e = Object::cast_to<Enemy>(Enemy::___get_from_variant(enemies.pop_front()));

            if(world_to_map(e->get_position().snapped(Vector2(tile_size, tile_size))) == attack_tile){
                e->call("take_damage", damage, direction);
            }
        }
    }

}