#include "enemy.h"
#include "player.h"
#include "raylib.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(){ std::cout<<"Enemy created\n";}

Enemy::Enemy(int speed, int damage, int health)
  : enemy_speed{ speed }
  , enemy_damage{ damage }
  , enemy_health{ health }
{
  std::cout<<"Speed: "<<this->enemy_speed<<std::endl;
  std::cout<<"Health: "<<this->enemy_health<<std::endl;
  std::cout<<"Damage: "<<this->enemy_damage<<std::endl;
  std::cout<<"Enemy created\n";
}

void Enemy::enemy_movement(Player player) {
  float dx = player.player_rect.x - this->enemy_rect.x;
  float dy = player.player_rect.y - this->enemy_rect.y;

  float length = sqrt(dx * dx + dy * dy);

  if(length != 0) {
    dx /= length;
    dy /= length;
  }

  this->enemy_rect.x += dx * enemy_speed;
  this->enemy_rect.y += dy * enemy_speed;
}

void Enemy::enemy_rotation(Player player) {
    this->deltaX = player.player_rect.x - this->enemy_rect.x; 
    this->deltaY = player.player_rect.y - this->enemy_rect.y; 

    e_rotation = (std::atan2(-deltaX, deltaY) * 180.000) / 3.141592;
}

int Enemy::get_enemy_speed(){ return this->enemy_speed;}
int Enemy::get_enemy_damage(){ return this->enemy_damage;}
int Enemy::get_enemy_health(){ return this->enemy_health;}

void Enemy::set_enemy_speed(int speed){ this->enemy_speed = speed;}
void Enemy::set_enemy_damage(int damage){ this->enemy_damage = damage;}
void Enemy::set_enemy_health(int health){ this->enemy_health = health;}

