#include "raylib.h"
#include <cmath>
#include <iostream>

void player_movement();
void player_rotation();
void player_shoot();

Rectangle enemy;
int e_rotation;
int eDeltaX;
int eDeltaY;

Rectangle player;
int p_rotation{ 0 };
int deltaX;
int deltaY;
Color player_color{ RED };
bool alive = true;

int player_speed{ 5 };
int player_damage{ 5 };
int player_health{ 100 };
int player_exp{ 0 };
int player_level{ 0 };

int main(void)
{
  const int screenWidth{ 1920 };
  const int screenHeight{ 1080 };

  InitWindow(screenWidth, screenHeight, "Super fun game");

  SetTargetFPS(60);
  //ToggleFullscreen();

  player.height = 50;
  player.width = 50;
  player.x = static_cast<float>(screenWidth)/2;
  player.y = static_cast<float>(screenHeight)/2;

  enemy.height = 50;
  enemy.width = 50;
  enemy.x = 1000;
  enemy.y = 700;

  while(!WindowShouldClose()) {
    if(IsKeyPressed(KEY_F)) player_health -= 5;
    if(IsKeyPressed(KEY_E)) player_exp += 50;

    player_level = player_exp*0.01;

    eDeltaX = enemy.x - player.x;
    eDeltaY = enemy.y - player.y;

    e_rotation = (std::atan2(-eDeltaX, eDeltaY) * 180.000) / 3.141592;

    if(alive) player_movement();
    player_rotation();
    player_shoot();

    BeginDrawing();
      ClearBackground(BLACK);

      //Draw Player
      DrawRectanglePro(player, {player.height/2, player.width/2}, p_rotation, player_color);

      //Draw enemy
      DrawRectanglePro(enemy, {enemy.height/2, enemy.width/2}, e_rotation, GREEN);

      //Draw Healthbar
      DrawRectangle(10, 10, 100, 10, GRAY);
      DrawRectangle(10, 10, player_health, 10, RED);
      
      //Draw exp counter
      DrawText(TextFormat("Level: %i", player_level), 10, 40, 20, WHITE);

      if(player_health <= 0) {
        DrawText("You died", screenWidth/2, screenHeight/2, 24, WHITE);
        alive = false;
      }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void player_movement()
{
    if(IsKeyDown(KEY_D)) player.x+=player_speed;
    if(IsKeyDown(KEY_A)) player.x-=player_speed;
    if(IsKeyDown(KEY_W)) player.y-=player_speed;
    if(IsKeyDown(KEY_S)) player.y+=player_speed;
}

void player_rotation()
{
    deltaX = player.x - GetMousePosition().x;
    deltaY = player.y - GetMousePosition().y;

    p_rotation = (std::atan2(-deltaX, deltaY) * 180.000) / 3.141592;
}

void player_shoot()
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) player_color = WHITE;
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) player_color = RED;
}
