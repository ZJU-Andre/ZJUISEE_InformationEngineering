//
// Created by kunlin on 2022/10/29.
//

#ifndef LAB3_CASTLE_H
#define LAB3_CASTLE_H

#include "room.h"
#include <vector>
using namespace std;
class Castle
{
private:
    vector<vector<Room> > map;
    int size;
    void _init(int);
    static const int COMMON = 0, MONSTER = 1, PRINCESS = 2, EXIT = 3, LOBBY = 4;
public:
    Castle();
    ~Castle();
    void printMap();
    void gaming();
};


#endif //LAB3_CASTLE_H
