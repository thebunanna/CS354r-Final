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
}

void Enemy::_process(float delta) {
    time_passed += delta;

    Vector2 direction = get_movedir();
    if(direction != Vector2())
        speed = MAX_SPEED;

    if(!is_moving && direction != Vector2()){
        movedir = direction.normalized();

        if(get_node("/root/Main/TileMap")->call("is_cell_vacant", get_position().snapped(Vector2(tile_size, tile_size)), movedir)){
            is_moving = true;   
            target_pos = get_node("/root/Main/TileMap")->call("update_child_pos", get_position().snapped(Vector2(tile_size, tile_size)), movedir);
        }
    }

    if(is_moving){
        
        speed = MAX_SPEED;
        velocity = speed * movedir * delta;

        float distance_to_target = get_position().distance_to(target_pos);
        float move_distance = velocity.length();

        if(distance_to_target < move_distance){

             velocity = movedir * distance_to_target;
             is_moving = false; 
        }

        move_and_collide(velocity);
    }
}

Vector2 Enemy::get_movedir(){

    Sprite* player = static_cast<godot::Sprite*>(get_node("/root/Main/Player"));
    Vector2 player_pos = player->get_position().snapped(Vector2(tile_size, tile_size));
    Vector2 my_pos = get_position().snapped(Vector2(tile_size, tile_size));

    PoolVector2Array path = get_node("/root/Main/TileMap")->call("get_path", my_pos, player_pos);
    
    Vector2 current_tile = my_pos / tile_size;

    Vector2 direction;

    if(path.size() > 1)
        direction = path[1] - current_tile;
    else
        direction = Vector2(0,0);

    if(current_tile + direction == player_pos / tile_size)
        direction = Vector2(0,0);
    
    if(direction.x != 0 && direction.y != 0)
        direction = Vector2(0,0);

    return direction;
}

void Enemy::init(Vector2 pos){
    set_position(pos.snapped(Vector2(tile_size, tile_size)));
}
