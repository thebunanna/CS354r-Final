#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <RayCast2D.hpp>

namespace godot {

    class Player : public Sprite {
        GODOT_CLASS(Player, Sprite)

    private:
        float time_passed;

        int tile_size = 64;

        float movespeed = 8;

        Vector2 last_pos;
        Vector2 target_pos;
        Vector2 movedir;

        RayCast2D* ray;

        float curHealth;
        float maxHealth;

        void get_movedir();

        bool still_moving();

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);
        
        float get_cur_health ();
        void modify_health (float delta);

        //void _input(Variant e);
    };

}

#endif
