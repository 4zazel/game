#include "raylib.h"
#include <cmath>
#include <iostream>

void player_movement();
void player_rotation();
void player_shoot();

Rectangle player;
int p_rotation = 0;
int deltaX;
int deltaY;
Color player_color = RED;

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

  while(!WindowShouldClose()) {

    player_movement();
    player_rotation();
    player_shoot();

    BeginDrawing();
      ClearBackground(BLACK);
      DrawRectanglePro(player, {player.height/2, player.width/2}, p_rotation, player_color);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void player_movement()
{
    if(IsKeyDown(KEY_D)) player.x+=5;
    if(IsKeyDown(KEY_A)) player.x-=5;
    if(IsKeyDown(KEY_W)) player.y-=5;
    if(IsKeyDown(KEY_S)) player.y+=5;

    std::cout<<"TEST"<<std::endl;
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
