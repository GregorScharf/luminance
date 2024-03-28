#include "MainProcess.hpp"
#include <SDL2/SDL.h>

#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

namespace engine {

typedef struct {
  float x;
  float y;
} Vec2;

class Moving_Object { // base class for all moving objects
public:
  SDL_Rect dest;
  SDL_Texture *texture;
  double rotation; // in degrees
  Vec2 *position;  // not the actual position on the screen,
  Moving_Object(SDL_Surface *SDL_Surface) {
    texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(),
                                           SDL_Surface);
    position = new Vec2;
    init();
  }
  virtual void init(){}; // user defined called after default constructor
  void render(SDL_Renderer *renderer) {
    dest.x = position->x;
    dest.y = position->y;
    SDL_RenderCopyEx(renderer, texture, NULL, &dest, rotation, NULL,
                     SDL_FLIP_NONE);
  }
  virtual void update() = 0;
  virtual ~Moving_Object() {
    SDL_DestroyTexture(texture);
    delete position;
  }
};

} // namespace engine

#endif
