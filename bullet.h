#pragma once
#include "raylib.h"

struct Bullet {
    Vector2 pos;
    Vector2 vel;
    int damage = 10;
    int radius = 4;
    float speed = 600;
};
