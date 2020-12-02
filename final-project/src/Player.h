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
        RayCast2D* ray;

        CollisionPolygon2D* hurtbox;

        bool still_moving();

        void end_hitstun();

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
