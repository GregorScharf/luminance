#include <luminance/include/engine.hpp>

/*
  before you read this, if you are using neovim with the clandg lsp it may show
  some errors, however since we are compiling wiht g++ it is no problem and will
  compile and work without any issues
*/

#ifndef ENEMY_CPP
#define ENEMY_CPP

namespace BaseEnemy {

constexpr SDL_Surface *load_surface(const char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL) {
    std::cerr << "Failed to load surface: " << path;
  }
  return surface;
}

SDL_Surface *surface = load_surface("assets/enemy.bmp");
SDL_Rect src = {0, 0, 32, 32};
long double std_Speed = 0.2f;

} // namespace BaseEnemy

class Enemy : public engine::Moving_Object { /*this works, ignore the lsp*/
public:
  Enemy() : engine::Moving_Object(BaseEnemy::surface) { dest = {0, 0, 32, 32}; }
  void init() override {
    texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(),
                                           BaseEnemy::surface);
    dest = {0, 0, 32, 32};
  }
  void update() override {}
  void chase_player(SDL_Rect destination, int deltaTime) {
    if (dest.x < destination.x) {
      position->x += BaseEnemy::std_Speed * deltaTime;
    } else {
      position->x -= BaseEnemy::std_Speed * deltaTime;
    }
    if (dest.y < destination.y) {
      position->y += BaseEnemy::std_Speed * deltaTime;
    } else {
      position->y -= BaseEnemy::std_Speed * deltaTime;
    }
  }
};

class EnemyManager {
public:
  static std::vector<Enemy *> enemies;
  static int enemy_count;
  int spawn_timer;
  float spawn_rate;
  EnemyManager() {
    spawn_timer = 0;
    enemy_count = 0;
  }
  void start() {
    spawn_timer = 0;
    enemy_count = 0;
    spawn_rate = engine::MainProcess::get_Fps() * 0.5;
  }
  void update(SDL_Rect *_player_pos) {
    if (spawn_timer == 1) {
      enemies.push_back(new Enemy());
      std::cout << "enemy made \n";
      enemy_count++;
    } else if (spawn_timer > spawn_rate) {
      spawn_timer = 0;
    }
    spawn_timer++;
    for (long unsigned int i = 0; i < enemies.size(); i++) {
      enemies[i]->chase_player(*_player_pos,
                               engine::MainProcess::get_delta_time());
    }
  }
  void render(SDL_Renderer *renderer) {
    for (long unsigned int i = 0; i < enemies.size(); i++) {
      enemies[i]->render(renderer);
    }
  }
  static void delete_enemy(int index) {
    delete enemies[index];
    enemies.erase(enemies.begin() + index);
    enemy_count--;
  }
  static void delete_enemy_iterator(std::vector<Enemy *>::iterator it) {
    delete *it;
    enemies.erase(it);
    enemy_count--;
    enemies.shrink_to_fit();
  }
};

std::vector<Enemy *> EnemyManager::enemies;
int EnemyManager::enemy_count;

#endif // ENEMY_CPP
