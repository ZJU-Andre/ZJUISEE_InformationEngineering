//
// Created by kunlin on 2022/10/29.
//
#include "player.h"
#include <iostream>
#include <string>
using namespace std;
Player::Player(int PosX, int PosY) : x(PosX), y(PosY), withPrincess(0) {};
Player::~Player() {};
bool Player::isWithPrincess()
{
    return withPrincess;
}
void Player::getPrincess()
{
    if (withPrincess)
        cout<<"The princess has followed with you!\n";
    withPrincess = 1;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

void Player::logIn()
{
    int count = 0;
    string word = "";
    if (x > 0)
        ++count, word += "east, ";
    if (y > 0)
        ++count, word += "up, ";
    if (x < 2)
        ++count, word += "west, ";
    if (y < 2)
        ++count, word += "down, ";
    cout<<"There are "<<count<<" exits: "<<word<<" which you choose?\n";
}

int Player::move(int offsetX, int offsetY)
{
    if (x + offsetX <0 || x + offsetX > 2)
        return 1;
    if (y + offsetY <0 || y + offsetY > 2)
        return 1;
    x += offsetX;
    y += offsetY;
    return 0;
}