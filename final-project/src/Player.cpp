#include "Player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("end_hitstun", &Player::end_hitstun);
    register_method("flicker", &Player::flicker);
    //register_method("_input", &Player::_input);
    register_signal<Player>((char *)"health_changed", "health", GODOT_VARIANT_TYPE_VECTOR2);

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

    hitstun_timer = Timer()._new();
    hitstun_timer->set_wait_time (1.5);
    hitstun_timer->set_one_shot (false);
    add_child (hitstun_timer);
    hitstun_timer->connect("timeout", this, "end_hitstun");

    flicker_timer = Timer()._new();
    flicker_timer->set_wait_time (.2);
    flicker_timer->set_one_shot (false);
    add_child (flicker_timer);
    flicker_timer->connect("timeout", this, "flicker");
    
    maxHealth = 100;
    curHealth = 0;
}

void Player::_ready(){
    set_position(Vector2(64,64).snapped(Vector2(tile_size, tile_size)));
    target_pos = get_position();
    hurtbox = Object::cast_to<CollisionPolygon2D>(CollisionPolygon2D::___get_from_variant(get_node("CollisionPolygon2D")));
    sprite = Object::cast_to<Sprite>(Sprite::___get_from_variant(get_node("Sprite")));

    modify_health(50);
}

void Player::_process(float delta) {
    time_passed += delta;
    velocity = Vector2(0, 0);
    
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

        if(in_hitstun)
            movedir = (target_pos - get_position()).normalized();

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
    }

    KinematicCollision2D* k = *move_and_collide(velocity);

    if(k != NULL){
        if(k->get_collider()->has_method("init")){

            in_hitstun = true;
            hitstun_timer->start();
            flicker_timer->start();
            hurtbox->set_disabled(true);
            sprite->set_modulate(Color(1,1,0));
            is_moving = true;

            movedir = k->get_normal();
            target_pos = get_node("/root/Main/TileMap")->call("get_hitstun_tile", get_position(), movedir);

            movedir = (target_pos - get_position()).normalized();

            modify_health(-20);
        }
    }
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

void Player::end_hitstun(){
    in_hitstun = false;
    hurtbox->set_disabled(false);
    hitstun_timer->stop();
    flicker_timer->stop();
    sprite->set_modulate(Color(1,1,1));
}

void Player::flicker(){
    if(sprite->get_modulate() == Color(1,1,1))
        sprite->set_modulate(Color(1,1,0));
    else
        sprite->set_modulate(Color(1,1,1));
}
float Player::get_cur_health () {
    return curHealth;
}
void Player::modify_health (float delta) {
    curHealth += delta;
    if (curHealth > maxHealth) curHealth = maxHealth;
    emit_signal("health_changed", Vector2(curHealth, maxHealth));

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
