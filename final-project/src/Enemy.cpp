#include "Enemy.h"

using namespace godot;

void Enemy::_register_methods() {
    register_method("_process", &Enemy::_process);
    register_method("_ready", &Enemy::_ready);
    register_method("init", &Enemy::init);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
    // add your cleanup here
}

void Enemy::_init() {
    // initialize any variables here
    time_passed = 0.0;
    movedir = Vector2(0, 0);
    
}

void Enemy::_ready(){
    set_position(Vector2(256, 256).snapped(Vector2(tile_size, tile_size)));
    target_pos = get_position();
    last_pos = get_position();
}

void Enemy::_process(float delta) {
    time_passed += delta;

    //120 fps
    if(time_passed >= 0.0083333){
        
        time_passed = 0.0;
        Vector2 position = get_position();

        position += movespeed * movedir;

        if(position.distance_to(last_pos) >= tile_size - movespeed){
            position = target_pos;
        }
                
        if(position == target_pos){
            get_movedir();
            last_pos = position;
            target_pos += movedir * tile_size;
        }

        set_position(position);
    }
}

void Enemy::get_movedir(){

    Sprite* player = static_cast<godot::Sprite*>(get_node("/root/Main/Player"));
    Vector2 player_pos = player->get_position().snapped(Vector2(tile_size, tile_size));
    Vector2 my_pos = get_position().snapped(Vector2(tile_size, tile_size));

    PoolVector2Array path = get_node("/root/Main/TileMap")->call("get_path", my_pos, player_pos);
    
    Vector2 current_tile = my_pos / tile_size;

    if(path.size() > 1)
        movedir = path[1] - current_tile;
    else
        movedir = Vector2(0,0);

    if(current_tile + movedir == player_pos / tile_size)
        movedir = Vector2(0,0);
    
    if(movedir.x != 0 && movedir.y != 0)
        movedir = Vector2(0,0);
}

void Enemy::init(Vector2 pos){
    set_position(pos.snapped(Vector2(tile_size, tile_size)));
}
