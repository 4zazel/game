#include "raylib.h"

#include "player.h"
#include "enemy.h"

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

  Enemy e = *new Enemy(3, 5, 100);

  e.enemy_rect.x = 1200.0f;
  e.enemy_rect.y = 540.0f;
  e.enemy_rect.height = 50;
  e.enemy_rect.width = 50;

  while(!WindowShouldClose()) {
    if(IsKeyPressed(KEY_F)) p.set_player_health(p.get_player_health()-5);
    if(IsKeyPressed(KEY_E)) p.set_player_exp(p.get_player_exp()+50);

    //Calculate player level
    p.set_player_level(p.get_player_exp()*0.01);

    e.enemy_movement(p);
    e.enemy_rotation(p);

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
      DrawRectanglePro(e.enemy_rect, {e.enemy_rect.height/2, e.enemy_rect.width/2}, e.e_rotation, e.enemy_color);

      //Draw Healthbar
      DrawRectangle(10, 10, 100, 10, GRAY);
      DrawRectangle(10, 10, p.get_player_health(), 10, RED);
      
      //Draw exp counter
      DrawText(TextFormat("Level: %i", p.get_player_level()), 10, 40, 20, WHITE);
      
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
