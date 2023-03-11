//
// Created by kunlin on 2022/10/29.
//

#include "castle.h"
#include "room.h"
#include "player.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
Castle::Castle()
{
    srand(time(NULL));
    size = 3;
    map.resize(size);
    for (vector < vector <Room> > :: iterator ri = map.begin(); ri != map.end(); ++ri)
    {
        for (int i = 0; i != 3; ++i)
        {
            Room room;
            ri->push_back(room);
        }
    }
    map[1][1].setType(LOBBY);
    _init(MONSTER);
    _init(PRINCESS);
    _init(EXIT);

}
Castle::~Castle() {};
void Castle::_init(int type)
{
    while (1)
    {
        int x = rand() % 3;
        int y = rand() % 3;
        if (map[x][y].getType() == COMMON)
        {
            map[x][y].setType(type);
            break;
        }
    }
}

void Castle::printMap()
{
    for (vector <vector <Room> > :: iterator ri = map.begin(); ri != map.end(); ++ri)
    {
        for (vector <Room> :: iterator iter = ri->begin(); iter != ri->end(); ++iter)
            cout<<iter->getType()<<' ';
        cout<<endl;
    }
}

void Castle::gaming()
{
    Player player(1, 1);
    while (1)
    {
        int x = player.getX();
        int y = player.getY();
        if (map[x][y].logIn(player))
        {
            cout<<"Game Over!\n";
            return ;
        }
        player.logIn();
        int offsetX = 0, offsetY = 0;
        while(1)
        {
            //cout<<"X: "<<player.getX()<< "Y: "<<player.getY()<<endl;
            cout<<"Enter your commend: ";
            string go, pos;
            cin>>go>>pos;
            if (go != "go")
            {
                cout<<"Invalid commend, please retry!\n";
                continue;
            }
            if (pos == "east")
            {
                offsetX = -1;
            }
            if (pos == "up")
            {
                offsetY = -1;
            }
            if (pos == "west")
            {
                offsetX = 1;
            }
            if (pos == "down")
            {
                offsetY = 1;
            }
            //cout<<"X off: "<<offsetX<<" Y off: "<<offsetY<<endl;
            if (player.move(offsetX, offsetY))
            {
                cout<<"Invalid direction, please retry!\n";
                continue;
            }
            if (player.getX() == x && player.getY() == y)
            {
                cout<<"You went to a wrong direction, please retry!\n";
                continue;
            }
            break;
        }
    }

}