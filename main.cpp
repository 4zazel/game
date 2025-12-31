#include <cmath>
#include "raylib.h"

#include "player.h"

//Temp
Rectangle enemy;
int e_rotation;
int eDeltaX;
int eDeltaY;

int main(void)
{
  const int screenWidth{ 1920 };
  const int screenHeight{ 1080 };

  InitWindow(screenWidth, screenHeight, "Super fun game");

  SetTargetFPS(60);
  //ToggleFullscreen();

  Player p = *new Player(5, 5, 100);

  p.player_rect.x = static_cast<float>(screenWidth)/2;
  p.player_rect.y = static_cast<float>(screenHeight)/2;
  p.player_rect.height = 50;
  p.player_rect.width = 50;

  //Temp
  enemy.height = 50;
  enemy.width = 50;
  enemy.x = 1000;
  enemy.y = 700;

  while(!WindowShouldClose()) {
    if(IsKeyPressed(KEY_F)) p.set_player_health(p.get_player_health()-5);
    if(IsKeyPressed(KEY_E)) p.set_player_exp(p.get_player_exp()+50);

    //Temp
    p.set_player_level(p.get_player_exp()*0.01);

    eDeltaX = enemy.x - p.player_rect.x;
    eDeltaY = enemy.y - p.player_rect.y;

    e_rotation = (std::atan2(-eDeltaX, eDeltaY) * 180.000) / 3.141592;

    if(enemy.x < p.player_rect.x) enemy.x += 3;
    if(enemy.x > p.player_rect.x) enemy.x -= 3;
    if(enemy.y < p.player_rect.y) enemy.y += 3;
    if(enemy.y > p.player_rect.y) enemy.y -= 3;

    if(p.alive) {
      p.player_movement();
      p.player_rotation();
      p.player_shoot();
    }

    BeginDrawing();
      ClearBackground(BLACK);

      //Draw Player
      DrawRectanglePro(p.player_rect, {p.player_rect.height/2, p.player_rect.width/2}, p.p_rotation, p.player_color);

      //Draw enemy
      DrawRectanglePro(enemy, {enemy.height/2, enemy.width/2}, e_rotation, GREEN);

      //Draw Healthbar
      DrawRectangle(10, 10, 100, 10, GRAY);
      DrawRectangle(10, 10, p.get_player_health(), 10, RED);
      
      //Draw exp counter
      DrawText(TextFormat("Level: %i", p.get_player_level()), 10, 40, 20, WHITE);

      if(p.get_player_health() <= 0) {
        DrawText("You died", screenWidth/2, screenHeight/2, 24, WHITE);
        p.alive = false;
      }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
