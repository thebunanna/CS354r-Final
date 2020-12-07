#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <RayCast2D.hpp>
#include <Timer.hpp>
#include <CollisionPolygon2D.hpp>
#include <Color.hpp>
#include <Area2D.hpp>

namespace godot {

    class Player : public KinematicBody2D {
        GODOT_CLASS(Player, KinematicBody2D)

    private:
        float time_passed;

        int tile_size = 64;
        const float MAX_SPEED = 400;
        float speed = 0;

        Vector2 velocity;
        Vector2 target_pos;
        Vector2 movedir;
        bool is_moving = false;
        bool in_hitstun = false;
        Timer* hitstun_timer;
        Timer* flicker_timer;
        Timer* attack_timer;
        RayCast2D* ray;

        CollisionPolygon2D* hurtbox;
        Sprite* sprite;
        Sprite* weapon;

        Area2D* area;

        void flicker();
        float curHealth;
        float maxHealth;
        float attack_damage = 20;

        bool dead = false;

        void get_movedir();

        bool still_moving();

        void end_hitstun();
        void end_attack();

        void check_attack();
        void check_death();

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);
        
        float get_cur_health ();
        void modify_health (float delta);

        Array get_interact ();
    };

}

#endif
