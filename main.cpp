#include "raylib.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <cstdlib>
#include <ctime>
#include <vector>

std::vector<Enemy> enemies = {};
std::vector<Bullet> bullets;

void spawnEnemy();
void resolveEnemyCollision(Enemy& a, Enemy& b);
void resolvePlayerCollision(Enemy& e, Player& p);
void spawnWaves();

int current_wave = 1;

int main(void)
{
  srand(time(0));

  const int screenWidth{ 1920 };
  const int screenHeight{ 1080 };

  bool is_fullscreen = false;

  InitWindow(screenWidth, screenHeight, "Super fun game");

  SetTargetFPS(60);
  ToggleFullscreen();

  Player p(5, 5, 100);

  p.player_rect.x = static_cast<float>(screenWidth)/2;
  p.player_rect.y = static_cast<float>(screenHeight)/2;
  p.player_rect.height = 50;
  p.player_rect.width = 50;

  while(!WindowShouldClose()) {

    float dt = GetFrameTime();

    if(IsKeyPressed(KEY_F)) ToggleFullscreen();

    if(IsKeyPressed(KEY_H)) p.set_player_health(p.get_player_health()-5);
    if(IsKeyPressed(KEY_E)) p.set_player_exp(p.get_player_exp()+50);
    if(IsKeyPressed(KEY_K)) enemies = {};
    if(IsKeyPressed(KEY_T)) spawnEnemy();

    spawnWaves();
    
    float deltaTime = GetFrameTime(); // time since last frame

    // Update player invulnerability timer
    if (p.inv_time > 0) {
      p.inv_time -= deltaTime;
      if (p.inv_time < 0){
        p.inv_time = 0;
        p.player_color = RED;
      }
    }

    if(p.fire_timer > 0.0f) p.fire_timer -= dt;

    //Calculate player level
    p.set_player_level(p.get_player_exp()*0.01);

    if(p.alive) {
      p.player_movement();
      p.player_rotation();
    }

    BeginDrawing();
      ClearBackground(BLACK);

      //Draw Player
      DrawRectanglePro(p.player_rect, {p.player_rect.height/2, p.player_rect.width/2}, p.p_rotation, p.player_color);

      //Draw enemy
      for(Enemy&e : enemies){
        if(e.get_enemy_health() > 0){
          DrawRectanglePro(e.enemy_rect, {e.enemy_rect.height/2, e.enemy_rect.width/2}, e.e_rotation, e.enemy_color);
        }
        if(e.get_enemy_health() != 100) DrawRectangle(e.enemy_rect.x - 50, e.enemy_rect.y - 50, e.get_enemy_health(), 5, RED);
        e.enemy_movement(p);
        e.enemy_rotation(p);

      }

      for(int i = 0; i < bullets.size(); i++) {
        bool bullet_hit = false;
        for(int j = 0; j<enemies.size(); j++) {
          if(CheckCollisionCircleRec(bullets[i].pos, bullets[i].radius + 10,enemies[j].enemy_rect)) {
            enemies[j].set_enemy_health(enemies[j].get_enemy_health() - bullets[i].damage);
            bullet_hit = true;
            break;
          }
        }
        if(bullet_hit) {
          bullets.erase(bullets.begin() + i);
          i--;
        }
      }

      for(int i = 0; i<enemies.size(); i++){
        if(enemies[i].get_enemy_health() == 0) {
          enemies.erase(enemies.begin() + i);
          i--;
        }
      }
      
      for (Bullet& b : bullets) {
        b.pos.x += b.vel.x * GetFrameTime();
        b.pos.y += b.vel.y * GetFrameTime();
      }

      
      for (Bullet& b : bullets) {
        DrawCircleV(b.pos, 4, WHITE);
      }

      if(p.alive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        p.player_attack(bullets);
      }

      for(int i = 0; i<enemies.size(); i++) {
        resolvePlayerCollision(enemies[i], p);
        for(int j = i + 1; j<enemies.size(); j++) {
         resolveEnemyCollision(enemies[i], enemies[j]); 
        }
      }

      //Draw Healthbar
      DrawRectangle(10, 10, 100, 10, GRAY);
      DrawRectangle(10, 10, p.get_player_health(), 10, RED);
      
      //Draw exp counter
      DrawText(TextFormat("Level: %i", p.get_player_level()), 10, 40, 20, WHITE);
     
      //Draw wave counter
      DrawText(TextFormat("Wave: %i", current_wave-1), GetScreenWidth()/2, 10, 20, WHITE);

      //Check if the player died
      if(p.get_player_health() <= 0) {
        DrawText("You died", screenWidth/2, screenHeight/2, 24, WHITE);
        p.alive = false;
      }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void spawnEnemy(){
  Enemy e(3, 15, 100);
  e.enemy_rect.height = 50;
  e.enemy_rect.width = 50;
  e.enemy_rect.x = GetRandomValue(0, GetScreenWidth());
  e.enemy_rect.y = GetRandomValue(0, GetScreenHeight());
  enemies.push_back(e);
}

void spawnWaves(){
  if(enemies.empty())
  {
    for(int i = 0; i<current_wave; i++) spawnEnemy();
    current_wave++;
  }
}

void resolveEnemyCollision(Enemy& a, Enemy& b) {
    if (CheckCollisionRecs(a.enemy_rect, b.enemy_rect))
    {
        float overlapX = std::min(a.enemy_rect.x + a.enemy_rect.width - b.enemy_rect.x,
                                  b.enemy_rect.x + b.enemy_rect.width - a.enemy_rect.x);

        float overlapY = std::min(a.enemy_rect.y + a.enemy_rect.height - b.enemy_rect.y,
                                  b.enemy_rect.y + b.enemy_rect.height - a.enemy_rect.y);

        if (overlapX < overlapY)
        {
            if (a.enemy_rect.x < b.enemy_rect.x)
            {
                a.enemy_rect.x -= overlapX / 2;
                b.enemy_rect.x += overlapX / 2;
            }
            else
            {
                a.enemy_rect.x += overlapX / 2;
                b.enemy_rect.x -= overlapX / 2;
            }
        }
        else
        {
            if (a.enemy_rect.y < b.enemy_rect.y)
            {
                a.enemy_rect.y -= overlapY / 2;
                b.enemy_rect.y += overlapY / 2;
            }
            else
            {
                a.enemy_rect.y += overlapY / 2;
                b.enemy_rect.y -= overlapY / 2;
            }
        }
    }
}

void resolvePlayerCollision(Enemy& e, Player& p) {
    if (CheckCollisionRecs(e.enemy_rect, p.player_rect))
    {
        if(p.inv_time <= 0) {
          p.set_player_health(p.get_player_health() - e.get_enemy_damage());
          p.player_color = WHITE;
          p.inv_time = 0.5f;
        }

        float overlapX = std::min(e.enemy_rect.x + e.enemy_rect.width - p.player_rect.x, p.player_rect.x + p.player_rect.width - e.enemy_rect.x);

        float overlapY = std::min(e.enemy_rect.y + e.enemy_rect.height - p.player_rect.y, p.player_rect.y + p.player_rect.height - e.enemy_rect.y);

        if (overlapX < overlapY){
            if (e.enemy_rect.x < p.player_rect.x){
                e.enemy_rect.x -= overlapX / 2;
                p.player_rect.x += overlapX / 2;
            }
            else{
                e.enemy_rect.x += overlapX / 2;
                p.player_rect.x -= overlapX / 2;
            }
        } else {
            if (e.enemy_rect.y < p.player_rect.y) {
                e.enemy_rect.y -= overlapY / 2;
                p.player_rect.y += overlapY / 2;
            } else {
                e.enemy_rect.y += overlapY / 2;
                p.player_rect.y -= overlapY / 2;
            }
        }
    }
}
