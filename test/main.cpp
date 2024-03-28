#include "enemy.cpp"
#include "player.cpp"
#include "shooter.cpp"
#include <luminance/include/engine.hpp>

std::vector<Bullet *> BulletManager::bullets;

class Example : MonoBehaviour {
public:
  Player player;
  BulletManager bullet_manager;
  EnemyManager enemy_manager;

  void start() override {
    player.texture = SDL_CreateTextureFromSurface(
        engine::MainProcess::get_renderer(), player.surface);
    bullet_manager.start();
    enemy_manager.start();
  }
  void update() override {
    enemy_manager.update(player.get_pos());
    bullet_manager.update();
  }
  void input(const Uint8 *key_state) override {
    if (key_state[SDL_SCANCODE_W]) {
      player.move(up, engine::MainProcess::get_delta_time());
    }
    if (key_state[SDL_SCANCODE_S]) {
      player.move(down, engine::MainProcess::get_delta_time());
    }
    if (key_state[SDL_SCANCODE_A]) {
      player.move(left, engine::MainProcess::get_delta_time());
    }
    if (key_state[SDL_SCANCODE_D]) {
      player.move(right, engine::MainProcess::get_delta_time());
    }
    if (key_state[SDL_SCANCODE_SPACE]) {
      bullet_manager.shoot(player.get_pos());
    }
  }
  void render(SDL_Renderer *renderer) override {
    bullet_manager.render(renderer);
    enemy_manager.render(renderer);
    player.render(renderer);
  }
};

int main() {
  Example test;
  MainProcess engine("hello World");
  return 0;
}
