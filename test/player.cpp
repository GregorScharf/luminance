#include <luminance/include/engine.hpp>
#include "shooter.cpp"

#ifndef PLAYER_CPP
#define PLAYER_CPP


using namespace engine;

const Vec2 up = {0, -1};
const Vec2 down = {0, 1};
const Vec2 left = {-1, 0};
const Vec2 right = {1, 0};

class Player
{
public:
    SDL_Rect src, dest;
    SDL_Texture *texture;
    SDL_Surface *surface;
    float Speed;
    Player()
    {
        Speed = 2;
        surface = SDL_LoadBMP("assets/player.bmp");
        src = {0, 0, 32, 32};
        dest = {64, 64, 32, 32};
    }
    Player(const char *path, int speed)
    {
        Speed = speed;
        surface = SDL_LoadBMP(path);
        src = {0, 0, 32, 32};
        dest = {0, 0, 32, 32};
    }

    void move(const Vec2 direction, int deltaTime)
    {
        dest.x += direction.x * Speed * deltaTime;
        dest.y += direction.y * Speed * deltaTime;
    }
    void render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, &src, &dest);
    }
    SDL_Rect* get_pos()
    {
        return &dest;
    }
};

#endif // PLAYER_CPP
