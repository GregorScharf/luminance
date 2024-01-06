#include <luminance/include/engine.hpp>
#include <cmath>

#ifndef SHOOTER_CPP
#define SHOOTER_CPP

typedef struct
{
    long double x;
    long double y;
} Vec2;

class BaseBullet
{
public:
    static SDL_Rect src;
    static SDL_Surface *surface;
    static long double Speed;
    BaseBullet()
    {
        Speed = 1.5;
        surface = SDL_LoadBMP("assets/bullet.bmp");
        src = {0, 0, 32, 32};
    }
};

long double BaseBullet::Speed;
SDL_Rect BaseBullet::src;
SDL_Surface *BaseBullet::surface;

class Bullet
{
public:
    SDL_Rect dest;
    Vec2 direction;
    int range;
    bool maxRangeReached;
    SDL_Texture *texture;

    Bullet(SDL_Rect _player_pos)
    {
        dest = {
            .x = _player_pos.x + (_player_pos.w / 2),
            .y = _player_pos.y + (_player_pos.h / 2),
            .w = 12,
            .h = 12,
        };
        Vec2 mouse_pos;
        Vec2 player_pos;
        mouse_pos.x = engine::MainProcess::get_mouse_position().x;
        mouse_pos.y = engine::MainProcess::get_mouse_position().y;
        player_pos.x = _player_pos.x;
        player_pos.y = _player_pos.y;

        long double angle = atan2(mouse_pos.y - player_pos.y, mouse_pos.x - player_pos.x);
        direction.x = cos(angle);
        direction.y = sin(angle);
        range = 0;
        maxRangeReached = false;
        texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(), BaseBullet::surface);
        std::cout << "bullet made \n";
    }

    void update()
    {
        dest.x += direction.x * BaseBullet::Speed * engine::MainProcess::get_delta_time();
        dest.y += direction.y * BaseBullet::Speed * engine::MainProcess::get_delta_time();
        range++;
        if (range > 1000)
        {
            maxRangeReached = true;
            SDL_DestroyTexture(texture);
        }
    }

    void render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, &BaseBullet::src, &dest);
    }
};

class BulletManager
{
public:
    static std::vector<Bullet *> bullets;
    void shoot(SDL_Rect _player_pos)
    {
        bullets.push_back(new Bullet(_player_pos));
    }
    void start()
    {
        std::cout << "Bullet Manager Started \n";
    }
    void update()
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->maxRangeReached)
            {
                delete bullets[i];
                delete_bullet(i);
                std::cout << "bullet deleted \n";
            }
            else
            {
                bullets[i]->update();
            }
        }
    }
    void render(SDL_Renderer *renderer)
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i]->render(renderer);
        }
    }
    void delete_bullet(int index)
    {
        bullets.erase(bullets.begin() + index);
    }
};

#endif