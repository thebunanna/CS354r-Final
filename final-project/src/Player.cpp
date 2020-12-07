#include "Player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("end_hitstun", &Player::end_hitstun);
    register_method("flicker", &Player::flicker);
    register_method("end_attack", &Player::end_attack);
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

    attack_timer = Timer()._new();
    attack_timer->set_wait_time (.25);
    attack_timer->set_one_shot (false);
    add_child (attack_timer);
    attack_timer->connect("timeout", this, "end_attack");
    
    maxHealth = 100;
    curHealth = 0;
}

void Player::_ready(){
    set_position(Vector2(64,64).snapped(Vector2(tile_size, tile_size)));
    target_pos = get_position();
    hurtbox = Object::cast_to<CollisionPolygon2D>(CollisionPolygon2D::___get_from_variant(get_node("CollisionPolygon2D")));
    sprite = Object::cast_to<Sprite>(Sprite::___get_from_variant(get_node("Sprite")));
    weapon = Object::cast_to<Sprite>(Sprite::___get_from_variant(get_node("Weapon")));
    modify_health(50);

    area = Object::cast_to<Area2D>(get_node(NodePath("./InteractArea")));
}

void Player::_process(float delta) {

    if(!dead){
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

        check_attack();

        KinematicCollision2D* k = *move_and_collide(velocity);
        

        if(k != NULL){
            Enemy* e = Object::cast_to<Enemy>(k->get_collider());
            if(e != NULL){

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

        check_death();
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

void Player::check_attack(){

    if(Input::get_singleton()->is_action_pressed("attack") && attack_timer->is_stopped()){

        if(movedir == Vector2(-1,0)){
            weapon->set_offset(Vector2(-16, -48));
            weapon->set_rotation_degrees(180);
        }else if(movedir == Vector2(0,1)){
            weapon->set_offset(Vector2(54, -48));
            weapon->set_rotation_degrees(90);
        }else if(movedir == Vector2(0,-1)){
            weapon->set_offset(Vector2(-16, 16));
            weapon->set_rotation_degrees(-90);
        }else{
            weapon->set_offset(Vector2(54, 16));
            weapon->set_rotation_degrees(0);
        }
        weapon->set_visible(true);
        attack_timer->start();

        get_node("/root/Main/TileMap")->call("attack", get_position(), movedir, attack_damage);

    }else if(!attack_timer->is_stopped()){
        get_node("/root/Main/TileMap")->call("attack", get_position(), movedir, attack_damage);
    }
}

void Player::end_attack(){
    
    weapon->set_visible(false);
    attack_timer->stop();   
}

void Player::check_death(){
    if(curHealth <= 0){
        modify_health(0 - curHealth);
        dead = true;
        sprite->set_modulate(Color(0,0,0));
        hitstun_timer->stop();
        flicker_timer->stop();
    }
}

Array Player::get_interact () {
    if (area != NULL) {
        return area->get_overlapping_areas ();
    }
    else {
        std::cout << "Oh no " << std::endl;
        return Array();
    }
}