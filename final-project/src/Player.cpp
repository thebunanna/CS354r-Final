#include "Player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    //register_method("_input", &Player::_input);
}

Player::Player() {
}

Player::~Player() {
    // add your cleanup here
}

void Player::_init() {
    // initialize any variables here
    time_passed = 0.0;
    velocity = Vector2();
}

void Player::_ready(){
    set_position(Vector2(64,64).snapped(Vector2(tile_size, tile_size)));
    last_pos = get_position();
    target_pos = get_position();
}

void Player::_process(float delta) {
    time_passed += delta;

    Vector2 direction = Vector2(0,0);
    speed = 0;

    if(Input::get_singleton()->is_action_pressed("move_up"))
        direction.y -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_down"))
        direction.y += 1;
    else if(Input::get_singleton()->is_action_pressed("move_left"))
        direction.x -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_right"))
        direction.x += 1;

    if(direction != Vector2())
        speed = MAX_SPEED;

    // velocity = speed * direction * delta;
    // move_and_collide(velocity);

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
            
            if(still_moving() && get_node("/root/Main/TileMap")->call("is_cell_vacant", get_position().snapped(Vector2(tile_size, tile_size)), movedir)){
                target_pos = get_node("/root/Main/TileMap")->call("update_child_pos", get_position().snapped(Vector2(tile_size, tile_size)), movedir);
            }else{
                velocity = movedir * distance_to_target;
                is_moving = false; 
            }
            
        }

        move_and_collide(velocity);
    }



    //120 fps
    // if(time_passed >= 0.0083333){
    //     time_passed = 0.0;

    //     ray = Object::cast_to<RayCast2D>(RayCast2D::___get_from_variant(get_node("MainCast")));
    //     Vector2 position = get_position();

    //     if(ray->is_colliding()){
    //         position = last_pos;
    //         target_pos = last_pos;

    //     }else{
    //         position += movespeed * movedir;

    //         if(position.distance_to(last_pos) >= tile_size - movespeed){
    //             //position = target_pos;

    //             if(still_moving()){
    //                 last_pos = target_pos;
    //                 target_pos += movedir * tile_size;
    //             }else{
    //                 position = target_pos;
    //             }
    //         }
                
    //     }

    //     if(position == target_pos){
    //         get_movedir();
    //         last_pos = position;
    //         target_pos += movedir * tile_size;
    //     }

    //     set_position(position);
    // }

}

bool Player::still_moving(){

    if(movedir == Vector2(0,0))
        return false;

    if(movedir.x != 0){
        if(movedir.x == 1)
            return Input::get_singleton()->is_action_pressed("move_right");
        else
            return Input::get_singleton()->is_action_pressed("move_left");
    }

    if(movedir.y != 0){
        if(movedir.y == 1)
            return Input::get_singleton()->is_action_pressed("move_down");
        else
            return Input::get_singleton()->is_action_pressed("move_up");
    }


    Godot::print("Should not print");
    return false;
}


Vector2 Player::get_movedir(){

    Vector2 direction = Vector2(0,0);

    if(Input::get_singleton()->is_action_pressed("move_up"))
        direction.y -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_down"))
        direction.y += 1;
    else if(Input::get_singleton()->is_action_pressed("move_left"))
        direction.x -= 1;
    else if(Input::get_singleton()->is_action_pressed("move_right"))
        direction.x += 1;

    //makes sure you can't move diagonally
    // if(movedir.x != 0 && movedir.y != 0)
    //     movedir = Vector2(0,0);

    // if(movedir != Vector2(0,0))
    //     ray->set_cast_to(movedir * tile_size / 2);

    return direction.normalized();
    
}


// void Player::_input(Variant e){

//     InputEvent* event = Object::cast_to<InputEvent>(InputEvent::___get_from_variant(e));

//     if(get_position() == target_pos){

//         movedir = Vector2(0,0);

//         if(Input::get_singleton()->is_action_pressed("move_up"))
//             movedir.y -= 1;
//         else if(Input::get_singleton()->is_action_pressed("move_down"))
//             movedir.y += 1;
//         else if(Input::get_singleton()->is_action_pressed("move_left"))
//             movedir.x -= 1;
//         else if(Input::get_singleton()->is_action_pressed("move_right"))
//             movedir.x += 1;

//         //makes sure you can't move diagonally
//         if(movedir.x == 0 && movedir.y == 0)
//             movedir = Vector2(0,0);

//         if(movedir != Vector2(0,0))
//             ray->set_cast_to(movedir * tile_size / 2);
        
//         last_pos = get_position();
//         target_pos += movedir * tile_size;
//     }
    
// }
