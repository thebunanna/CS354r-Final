#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

    class Player : public Sprite {
        GODOT_CLASS(Player, Sprite)

    private:
        float time_passed;

    public:
        static void _register_methods();

        Player();
        ~Player();

        void _init(); // our initializer called by Godot

        void _process(float delta);
    };

}

#endif