#ifndef ITEMBANK_H
#define ITEMBANK_H

#include <Godot.hpp>
#include <Texture.hpp>
#include <Node.hpp>

namespace godot {
    
    class ItemTextures : public Node {
        GODOT_CLASS(ItemTextures, Node)

    private:
        Array textures;
    public:
        static void _register_methods();

        ItemTextures();
        ~ItemTextures();

        void _init();

        void _ready();
        
        void _reload_textures();

        Ref<Texture> _get_texture (int index);
    };

}

#endif