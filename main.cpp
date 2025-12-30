#include "raylib.h"
#include <cmath>
#include <iostream>

int main(void)
{
  const int screenWidth{ 1920 };
  const int screenHeight{ 1080 };

  InitWindow(screenWidth, screenHeight, "Super fun game");

  SetTargetFPS(60);
  //ToggleFullscreen();

  Rectangle player;
  player.height = 50;
  player.width = 50;
  player.x = static_cast<float>(screenWidth)/2;
  player.y = static_cast<float>(screenHeight)/2;

  int player_rotation = 0;

  int deltaX;
  int deltaY;

  while(!WindowShouldClose()) {

    deltaX = player.x - GetMousePosition().x;
    deltaY = player.y - GetMousePosition().y;

    player_rotation = (std::atan2(-deltaX, deltaY) * 180.000) / 3.141592;
    std::cout<<player_rotation<<std::endl;

    if(IsKeyDown(KEY_D)) player.x+=5; 
    if(IsKeyDown(KEY_A)) player.x-=5;
    if(IsKeyDown(KEY_W)) player.y-=5;
    if(IsKeyDown(KEY_S)) player.y+=5;

    BeginDrawing();
      ClearBackground(BLACK);
      DrawRectanglePro(player, {player.height/2, player.width/2}, player_rotation, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
