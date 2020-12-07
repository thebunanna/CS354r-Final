#include "Enemy.h"

using namespace godot;

void Enemy::_register_methods() {
    register_method("_process", &Enemy::_process);
    register_method("_ready", &Enemy::_ready);
    register_method("init", &Enemy::init);
    register_method("take_damage", &Enemy::take_damage);
    register_method("end_hitstun", &Enemy::end_hitstun);
    register_method("flicker", &Enemy::flicker);
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
    curr_health = 80;

    flicker_timer = Timer()._new();
    flicker_timer->set_wait_time (.1);
    flicker_timer->set_one_shot (false);
    add_child (flicker_timer);
    flicker_timer->connect("timeout", this, "flicker");

    hitstun_timer = Timer()._new();
    hitstun_timer->set_wait_time (1.5);
    hitstun_timer->set_one_shot (false);
    add_child (hitstun_timer);
    hitstun_timer->connect("timeout", this, "end_hitstun");

}

void Enemy::_ready(){
    set_position(Vector2(256, 256).snapped(Vector2(tile_size, tile_size)));
    target_pos = get_position();

    sprite = Object::cast_to<Sprite>(Sprite::___get_from_variant(get_node("Sprite")));
    hitbox = Object::cast_to<CollisionPolygon2D>(CollisionPolygon2D::___get_from_variant(get_node("CollisionPolygon2D")));
}

void Enemy::_process(float delta) {

    if(flag){
        set_position(get_node("/root/Main/TileMap")->call("get_random_position"));
        flag = false;
    }

    check_death();

    if(!dead){
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
}

Vector2 Enemy::get_movedir(){

    Sprite* player = static_cast<godot::Sprite*>(get_node("/root/Main/Player"));
    Vector2 player_pos = player->get_position().snapped(Vector2(tile_size, tile_size));
    Vector2 my_pos = get_position().snapped(Vector2(tile_size, tile_size));

    Vector2 direction = Vector2();


    if(player_pos.distance_to(my_pos) < tile_size * 10){
        PoolVector2Array path = get_node("/root/Main/TileMap")->call("get_path", my_pos, player_pos);
        
        Vector2 current_tile = my_pos / tile_size;

        if(path.size() > 1)
            direction = path[1] - current_tile;
        else
            direction = Vector2(0,0);

        if(current_tile + direction == player_pos / tile_size)
            direction = Vector2(0,0);
        
        if(direction.x != 0 && direction.y != 0)
            direction = Vector2(0,0);
    }

    

    return direction;
}

void Enemy::init(Vector2 pos){
    set_position(pos.snapped(Vector2(tile_size, tile_size)));
}

void Enemy::take_damage(float damage, Vector2 attack_direction){

    if(!in_hitstun){
        curr_health -= damage;
        target_pos = get_node("/root/Main/TileMap")->call("get_hitstun_tile", get_position(), attack_direction);
        movedir = (target_pos - get_position()).normalized();
        is_moving = true;
        hitstun_timer->start();
        flicker_timer->start();
        in_hitstun = true;
    }
    
}

void Enemy::end_hitstun(){
    in_hitstun = false;
    hitstun_timer->stop();
    flicker_timer->stop();
    sprite->set_modulate(Color(1,1,1));
}

void Enemy::flicker(){
    if(sprite->get_modulate() == Color(1,1,1))
        sprite->set_modulate(Color(0,1,0));
    else
        sprite->set_modulate(Color(1,1,1));
}

void Enemy::check_death(){
    if(curr_health <= 0){
        curr_health = 0;
        sprite->set_modulate(Color(0,0,0));
        in_hitstun = false;
        dead = true;
        hitstun_timer->stop();
        flicker_timer->stop();
        hitbox->set_disabled(true);
    }
}