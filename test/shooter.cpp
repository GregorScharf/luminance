#include <luminance/include/engine.hpp>
#include <cmath>

#ifndef SHOOTER_CPP
#define SHOOTER_CPP


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

class Bullet : engine::Moving_Object{
    public:
    engine::Vec2 *direction;
    int16_t range;
    bool maxRangeReached;
    Bullet(SDL_Surface *surface, SDL_Rect* player_pos) : engine::Moving_Object(surface)
    {
        texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(), surface);

        dest.x = player_pos->x;
        dest.y = player_pos->y;
        dest.w = 12;
        dest.h = 12;

        direction = new engine::Vec2;


        engine::Vec2 difference; 
        difference.x = engine::MainProcess::get_mouse_position().x - player_pos->x;
        difference.y = engine::MainProcess::get_mouse_position().y - player_pos->y;

        long double length = sqrt((difference.x * difference.x) + (difference.y * difference.y));

        direction->x = difference.x / length;
        direction->y = difference.y / length;

        position->x = dest.x;
        position->y = dest.y;

        range = 0;
        maxRangeReached = false;

    }
    void update(){
        position->x += direction->x * BaseBullet::std_Speed * engine::MainProcess::get_delta_time();
        position->y += direction->y * BaseBullet::std_Speed * engine::MainProcess::get_delta_time();
        dest.x = position->x;
        dest.y = position->y;
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

class BulletManager{
public:
    float shooting_cooldown;
    int active_cooldown;
    static std::vector<Bullet *> bullets;
    void shoot(SDL_Rect *_player_pos)
    {
        if(active_cooldown > shooting_cooldown){
            bullets.push_back(new Bullet(BaseBullet::surface, _player_pos));
            active_cooldown = 0;
        }
        
    }
    void start()
    {
        shooting_cooldown = 0.2f*engine::MainProcess::get_Fps();
        active_cooldown = 0;
        std::cout << "Bullet Manager Started \n";
    }
    void update()
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->maxRangeReached)
            {
                delete bullets[i]; // free memory
                delete_bullet(i); // delete reference
            }
            else
            {
                bullets[i]->update();
            }
        }
        active_cooldown++;
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