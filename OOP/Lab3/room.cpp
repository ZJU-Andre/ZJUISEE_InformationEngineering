//
// Created by kunlin on 2022/10/29.
//
#include "room.h"
#include <iostream>
using namespace std;

Room::Room():type(0) {};
int Room::logIn(Player & player)
{
    //cout<<"type: "<<type<<" player: X"<<player.getX()<<" Y:"<<player.getY()<<endl;
    switch(type)
    {
        case LOBBY:
            cout<<"Welcome to the lobby. \n";
            break;
        case MONSTER:
            cout<<"You went into a room with monster. \n";
            cout<<("You DIED" + (string)(player.isWithPrincess() ? " with princess!" : "!") + "\n");
            return 1;
        case PRINCESS:
            cout<<"You went into a room with princess. \n";
            player.getPrincess();
            break;
        case EXIT:
            cout<<"You went into the exit of the castle. \n";
            cout<<"You are safe " + (string)(player.isWithPrincess() ? "With princess!!" : ", but the princess were lost in the castle!");
            return 1;
        case COMMON:
            cout<<"You went into a common room, nothing happened. \n";
            break;
    }
    return 0;
};
void Room::setType(int t)
{
    type = t;
}
int Room::getType()
{
    return type;
}
Room::~Room() {};