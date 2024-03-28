#include "enemy.cpp"
#include <cmath>
#include <luminance/include/engine.hpp>
#define PI 3.14159265

#ifndef SHOOTER_CPP
#define SHOOTER_CPP

namespace BaseBullet {

constexpr SDL_Surface *load_surface(const char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL) {
    std::cerr << "Failed to load surface: " << path;
  }
  return surface;
}

SDL_Surface *surface = load_surface("assets/bullet.bmp");
constexpr SDL_Rect src = {0, 0, 32, 32};
constexpr long double std_Speed = 3.0f;

int maxRange;

void maxRange_init() { maxRange = 10 * engine::MainProcess::get_Fps(); }

} // namespace BaseBullet

class Bullet : public engine::Moving_Object {
public:
  int index;
  engine::Vec2 *direction;
  int16_t range;
  bool maxRangeReached;
  Bullet(SDL_Surface *surface, SDL_Rect *player_pos, int i)
      : engine::Moving_Object(surface) {
    texture = SDL_CreateTextureFromSurface(engine::MainProcess::get_renderer(),
                                           surface);

    dest.x = player_pos->x;
    dest.y = player_pos->y;
    dest.w = 12;
    dest.h = 12;

    direction = new engine::Vec2;

    engine::Vec2 difference;
    difference.x = engine::MainProcess::get_mouse_position().x - player_pos->x;
    difference.y = engine::MainProcess::get_mouse_position().y - player_pos->y;

    float length = std::hypot(difference.y, difference.x);

    direction->x = difference.x / length;
    direction->y = difference.y / length;

    position->x = dest.x;
    position->y = dest.y;

    range = 0;
    maxRangeReached = false;
    index = i;
  }
  void precise_collision();

  void update() {
    position->x += direction->x * BaseBullet::std_Speed *
                   engine::MainProcess::get_delta_time();
    position->y += direction->y * BaseBullet::std_Speed *
                   engine::MainProcess::get_delta_time();
    dest.x = position->x;
    dest.y = position->y;
    range++;
    if (range > BaseBullet::maxRange) {
      maxRangeReached = true;
      SDL_DestroyTexture(texture);
    }
    precise_collision();
  }
};

class BulletManager {
public:
  float shooting_cooldown;
  int active_cooldown;
  int bullet_count;
  static std::vector<Bullet *> bullets;
  void shoot(SDL_Rect *_player_pos) {
    if (active_cooldown > shooting_cooldown) {
      bullets.push_back(
          new Bullet(BaseBullet::surface, _player_pos, bullet_count));
      active_cooldown = 0;
      bullet_count++;
    }
  }
  void start() {
    BaseBullet::maxRange_init();
    shooting_cooldown = 0.1f * engine::MainProcess::get_Fps();
    active_cooldown = 0;
    bullet_count = 0;
    std::cout << "Bullet Manager Started \n";
  }
  void update() {
    for (long unsigned int i = 0; i < bullets.size(); i++) {
      if (bullets[i]->maxRangeReached) {
        delete bullets[i]; // free memory
        delete_bullet(i);  // delete reference
      } else {
        bullets[i]->update();
      }
    }
    active_cooldown++;
  }
  void render(SDL_Renderer *renderer) {
    for (long unsigned int i = 0; i < bullets.size(); i++) {
      bullets[i]->render(renderer);
    }
  }
  void delete_bullet(int index) {
    bullets.erase(bullets.begin() + index);
    bullet_count--;
  }
};

void Bullet::precise_collision() {
  for (long unsigned int i = 0; i < EnemyManager::enemies.size(); i++) {
    if (SDL_HasIntersection(&dest, &EnemyManager::enemies[i]->dest)) {
      EnemyManager::delete_enemy(i);
    }
  }
}

#endif
