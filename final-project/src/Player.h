#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>

namespace godot {

    class Player : public Sprite {
        GODOT_CLASS(Player, Sprite)

    private:
        float time_passed;

        int tile_size = 64;

        float movespeed = 256;

        Vector2 last_pos;
        Vector2 target_pos;
        Vector2 movedir;

        void get_movedir();

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);
    };

}

#endif