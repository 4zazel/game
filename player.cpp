#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include "bullet.h"

Player::Player(){ std::cout<<"Player created\n";}

Player::Player(int speed, int damage, int health)
  : player_speed{ speed }
  , player_damage{ damage }
  , player_health{ health }
{
  std::cout<<"Speed: "<<this->player_speed<<std::endl;
  std::cout<<"Health: "<<this->player_health<<std::endl;
  std::cout<<"Damage: "<<this->player_damage<<std::endl;
}

void Player::player_movement()
{
    if(IsKeyDown(KEY_D)) this->player_rect.x+=player_speed;
    if(IsKeyDown(KEY_A)) this->player_rect.x-=player_speed;
    if(IsKeyDown(KEY_W)) this->player_rect.y-=player_speed;
    if(IsKeyDown(KEY_S)) this->player_rect.y+=player_speed;
}

void Player::player_rotation()
{
    this->deltaX = this->player_rect.x - GetMousePosition().x;
    this->deltaY = this->player_rect.y - GetMousePosition().y;

    p_rotation = (std::atan2(-deltaX, deltaY) * 180.000) / 3.141592;
}

void Player::player_attack(std::vector<Bullet>& bullets)
{
    if(fire_timer > 0.0f) return;

    Bullet b;
    b.pos = { player_rect.x, player_rect.y };

    Vector2 mouse = GetMousePosition();
    Vector2 dir = Vector2Normalize({
        mouse.x - b.pos.x,
        mouse.y - b.pos.y
    });

    b.vel = { dir.x * b.speed, dir.y * b.speed };
    bullets.push_back(b);

}

int Player::get_player_speed(){ return this->player_speed;}
int Player::get_player_damage(){ return this->player_damage;}
int Player::get_player_health(){ return this->player_health;}
int Player::get_player_exp(){ return this->player_exp;}
int Player::get_player_level(){ return this->player_level;}

void Player::set_player_speed(int speed){ this->player_speed = speed;}
void Player::set_player_damage(int damage){ this->player_damage = damage;}
void Player::set_player_health(int health){ this->player_health = health;}
void Player::set_player_exp(int exp){ this->player_exp = exp;}
void Player::set_player_level(int lvl){ this->player_level = lvl;}

