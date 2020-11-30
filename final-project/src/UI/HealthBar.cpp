#include "HealthBar.h"

#include <SceneTree.hpp>
#include <Node.hpp>
#include <Label.hpp>
#include <Viewport.hpp>

using namespace godot;

void HealthBar::_register_methods() {
    register_method("_ready", &HealthBar::_ready);
    register_method("update", &HealthBar::update);

}

HealthBar::HealthBar() {
}

HealthBar::~HealthBar() {
    // add your cleanup here
}
void HealthBar::_init() {
}

void HealthBar::_ready(){
    hp_text = Object::cast_to<Label>(get_node(NodePath("HPText/BG/Text")));
    hp_bar = Object::cast_to<TextureProgress>(get_node(NodePath("Bar")));

    get_node(NodePath("/root/Main/Player"))->connect("health_changed", this, "update");
}

void HealthBar::update(Vector2 health) {
    hp_text->set_text(String::num(health.x));
    hp_bar->set_max(health.y);
    hp_bar->set_value(health.x);
    Godot::print(String::num(hp_bar->get_max()));
}