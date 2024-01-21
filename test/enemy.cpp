#include <luminance/include/engine.hpp>

#ifndef ENEMY_CPP
#define ENEMY_CPP

class BaseEnemy
{
public:
    static SDL_Rect src;
    static SDL_Surface *surface;
    static long double std_Speed;

    void init()
    {
        std_Speed = 0.002;
        surface = SDL_LoadBMP("assets/enemy.bmp");
        src = {0, 0, 32, 32};
    }
};  

long double BaseEnemy::std_Speed;
SDL_Rect BaseEnemy::src;
SDL_Surface *BaseEnemy::surface;

class Enemy
{
public:
    SDL_Rect dest;
    SDL_Texture *texture;
    Enemy()
    {
        texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(), BaseEnemy::surface);
        dest = {0, 0, 32, 32};
    }

    void chase_player(SDL_Rect destination, int deltaTime)
    {
        
    }
    void render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, &BaseEnemy::src, &dest);
    }
};

class EnemyManager
{
public:
    static std::vector<Enemy *> enemies;
    int enemy_count;
    int spawn_timer;
    float spawn_rate;
    EnemyManager()
    {
        spawn_timer = 0;
        enemy_count = 0;
    } 
    void start(){
        spawn_rate = engine::MainProcess::get_Fps() * 5;
    }
    void update(SDL_Rect *_player_pos)
    {
        if (spawn_timer == 1)
        {
            enemies.push_back(new Enemy());
            std::cout << "enemy made \n";
            enemy_count++;
        }
        else if (spawn_timer > spawn_rate)
        {
            spawn_timer = 0;
        }
        spawn_timer++;
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->chase_player(*_player_pos, engine::MainProcess::get_delta_time());
        }
    }
    void render(SDL_Renderer *renderer)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->render(renderer);
        }
    }
    void delete_enemy(int index)
    {
        enemies.erase(enemies.begin() + index);
        enemy_count--;
    }
};

#endif // ENEMY_CPP
