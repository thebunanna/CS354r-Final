#include "Player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
}

Player::Player() {
}

Player::~Player() {
    // add your cleanup here
}

void Player::_init() {
    // initialize any variables here
    time_passed = 0.0;
}

void Player::_ready(){
    set_position(get_position().snapped(Vector2(tile_size, tile_size)));
    last_pos = get_position();
    target_pos = get_position();
}

void Player::_process(float delta) {
    time_passed += delta;

    Vector2 position = get_position();

    position += movespeed * movedir * delta;

    if(position.distance_to(last_pos) >= tile_size - movespeed * delta)
        position = target_pos;

    if(position == target_pos){
        get_movedir();
        last_pos = position;
        target_pos += movedir * tile_size;
    }

    set_position(position);
}


void Player::get_movedir(){

    movedir = Vector2(0,0);

    if(Input::get_singleton()->is_action_pressed("move_up"))
        movedir.y -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_down"))
        movedir.y += 1;
    else if(Input::get_singleton()->is_action_pressed("move_left"))
        movedir.x -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_right"))
        movedir.x += 1;

    //makes sure you can't move diagonally
    if(movedir.x == 0 && movedir.y == 0)
        movedir = Vector2(0,0);

}