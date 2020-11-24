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
    
}

void Enemy::_ready(){
    set_position(Vector2(640, 256).snapped(Vector2(tile_size, tile_size)));
    target_pos = get_position();
    last_pos = get_position();
}

void Enemy::_process(float delta) {
    time_passed += delta;

    //120 fps
    if(time_passed >= 0.0083333){
        
    }
}

void Enemy::get_movedir(){
    
}

void Enemy::init(Vector2 pos){
    set_position(pos.snapped(Vector2(tile_size, tile_size)));
}
