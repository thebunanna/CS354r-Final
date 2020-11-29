#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <RayCast2D.hpp>

namespace godot {

    class Player : public KinematicBody2D {
        GODOT_CLASS(Player, KinematicBody2D)

    private:
        float time_passed;

        int tile_size = 64;
        const float MAX_SPEED = 400;
        float speed = 0;

        Vector2 velocity;
        Vector2 last_pos;
        Vector2 target_pos;
        Vector2 movedir;
        bool is_moving = false;

        RayCast2D* ray;

        Vector2 get_movedir();

        bool still_moving();

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init(); // our initializer called by Godot

        void _ready();

        void _process(float delta);

        //void _input(Variant e);
    };

}

#endif
