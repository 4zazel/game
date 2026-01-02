#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "raylib.h"

class Enemy{
  private:
    int enemy_speed{ 3 };
    int enemy_damage{ 5 };
    int enemy_health{ 100 };
  public:
    Color enemy_color{ GREEN };
    Rectangle enemy_rect;
    Rectangle collision_rect;
    int deltaX{ 0 };
    int deltaY{ 0 };
    int e_rotation{ 0 };
    bool alive{ true };
    float inv_time{ 1 };

    Enemy();
    Enemy(int speed, int damage, int health);

    void enemy_movement(Player player);
    void enemy_rotation(Player player);

    int get_enemy_speed();
    int get_enemy_damage();
    int get_enemy_health();

    void set_enemy_speed(int speed);
    void set_enemy_damage(int damage);
    void set_enemy_health(int health);
};

#endif // !ENEMY_H
