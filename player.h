#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player{
  private:
    int player_speed{ 5 };
    int player_damage{ 5 };
    int player_health{ 100 };
    int player_exp{ 0 };
    int player_level{ 0 };
  public:  
    Color player_color{ RED };
    Rectangle player_rect;
    int deltaX{ 0 };
    int deltaY{ 0 };
    int p_rotation{ 0 };
    bool alive{ true };

    Player();
    Player(int speed, int damage, int health);

    void player_movement();
    void player_rotation();
    void player_shoot();

    int get_player_speed();
    int get_player_damage();
    int get_player_health();
    int get_player_exp();
    int get_player_level();

    void set_player_speed(int speed);
    void set_player_damage(int damage);
    void set_player_health(int health);
    void set_player_exp(int exp);
    void set_player_level(int lvl);
};


#endif // !PLAYER_H
