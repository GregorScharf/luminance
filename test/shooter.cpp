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
    static long double std_Speed;
    static int maxRange;

    void init(){
        maxRange = 10*engine::MainProcess::get_Fps();
        std_Speed = 2.0f;
        surface = SDL_LoadBMP("assets/bullet.bmp");
        src = {0, 0, 32, 32};
    
    }
};

long double BaseBullet::std_Speed;
SDL_Rect BaseBullet::src;
SDL_Surface *BaseBullet::surface;
int BaseBullet::maxRange;

class Bullet
{
public:
    Vec2 virtual_pos;
    SDL_Rect dest;
    Vec2 direction;
    int range;
    bool maxRangeReached;
    SDL_Texture *texture;
    Vec2 speed;

    Bullet(SDL_Rect _player_pos)
    {
        dest = { 
            .x = _player_pos.x,
            .y = _player_pos.y,
            .w = 12,
            .h = 12,
        };
        Vec2 mouse_pos;
        Vec2 player_pos;
        Vec2 difference;
        mouse_pos.x = engine::MainProcess::get_mouse_position().x;
        mouse_pos.y = engine::MainProcess::get_mouse_position().y;
        player_pos.x = _player_pos.x;
        player_pos.y = _player_pos.y;
        difference.x = mouse_pos.x - player_pos.x;
        difference.y = mouse_pos.y - player_pos.y;

        // i cannot get this to be fully accurate, any suggestions are welcome

        long double length = sqrt((difference.x * difference.x) + (difference.y * difference.y));

        direction.x = difference.x / length;
        direction.y = difference.y / length;

        virtual_pos = {player_pos.x, player_pos.y};
        range = 0;
        maxRangeReached = false;
        texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(), BaseBullet::surface);
    }

    void update()
    {
        virtual_pos.x += direction.x * BaseBullet::std_Speed * engine::MainProcess::get_delta_time();
        virtual_pos.y += direction.y * BaseBullet::std_Speed * engine::MainProcess::get_delta_time();
        dest.x = virtual_pos.x;
        dest.y = virtual_pos.y;
        range++;
        if (range > BaseBullet::maxRange)
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