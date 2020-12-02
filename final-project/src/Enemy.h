#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>


namespace godot {

    class Enemy : public KinematicBody2D {
        GODOT_CLASS(Enemy, KinematicBody2D)

    private:
        float time_passed;

        int tile_size = 64;
        const float MAX_SPEED = 200;
        float speed = 0;

        Vector2 target_pos;
        Vector2 movedir;
        Vector2 velocity;
        bool is_moving = false;


    public:
        static void _register_methods();

        Enemy();
        ~Enemy();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);

        Vector2 get_movedir();

        void init(Vector2 pos);
    };

}

#endif
