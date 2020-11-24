#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

    class Enemy : public Sprite {
        GODOT_CLASS(Enemy, Sprite)

    private:
        float time_passed;

        int tile_size = 64;

        float movespeed = 4;

        Vector2 last_pos;
        Vector2 target_pos;
        Vector2 movedir;

    public:
        static void _register_methods();

        Enemy();
        ~Enemy();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);

        void get_movedir();

        void init(Vector2 pos);
    };

}

#endif
