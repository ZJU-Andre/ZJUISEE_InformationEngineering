//
// Created by kunlin on 2022/10/29.
//

#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

class Player
{
private:
    int x, y;
    bool withPrincess;
public:
    Player(int, int);
    ~Player();
    bool isWithPrincess();
    void getPrincess();
    int getX();
    int getY();
    void logIn();
    int move(int, int);

};

#endif //LAB3_PLAYER_H
