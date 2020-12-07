#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <Timer.hpp>
#include <Color.hpp>
#include <CollisionPolygon2D.hpp>

namespace godot {

    class Enemy : public KinematicBody2D {
        GODOT_CLASS(Enemy, KinematicBody2D)

    private:
        float time_passed;

        int tile_size = 64;
        const float MAX_SPEED = 200;
        float speed = 0;

        bool flag = true;

        Sprite* sprite;
        CollisionPolygon2D* hitbox;

        Vector2 target_pos;
        Vector2 movedir;
        Vector2 velocity;
        bool is_moving = false;
        bool in_hitstun = false;
        Timer* hitstun_timer;
        Timer* flicker_timer;

        bool dead = false;

        float curr_health;

        void end_hitstun();
        void flicker();

        void check_death();

    public:
        static void _register_methods();

        Enemy();
        ~Enemy();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);

        void take_damage(float damage, Vector2 attack_direction);

        Vector2 get_movedir();

        void init(Vector2 pos);
    };

}

#endif
