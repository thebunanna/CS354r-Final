#ifndef HBAR_H
#define HBAR_H

#include <Godot.hpp>
#include <HBoxContainer.hpp>
#include <Label.hpp>
#include <TextureProgress.hpp>
namespace godot {

    class HealthBar : public HBoxContainer {
        GODOT_CLASS(HealthBar, HBoxContainer)

    private:
        Label* hp_text;
        TextureProgress* hp_bar;
    public:

        static void _register_methods();

        HealthBar();
        ~HealthBar();

        void _init();
        void _ready();

        void update(Vector2 health);
    };

}

#endif