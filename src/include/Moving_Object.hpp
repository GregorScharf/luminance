#include <SDL2/SDL.h>
#include "MainProcess.hpp"


#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

namespace engine{

typedef struct
{
    float x;
    float y;
} Vec2;

class Moving_Object{
    public:
    SDL_Rect dest;
    SDL_Texture *texture;
    Vec2 *position; // not the actual position on the screen, 
    Moving_Object(SDL_Surface* SDL_Surface){
        texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(), SDL_Surface);
        position = new Vec2;
    }
};
}


#endif