//
// Created by kunlin on 2022/10/29.
//

#ifndef LAB3_ROOM_H
#define LAB3_ROOM_H

#include "player.h"
class Room
{
private:
    int type;
    static const int COMMON = 0, MONSTER = 1, PRINCESS = 2, EXIT = 3, LOBBY = 4;
public:

    Room();
    ~Room();
    int logIn(Player &);
    void setType(int);
    int getType();

};


#endif //LAB3_ROOM_H
