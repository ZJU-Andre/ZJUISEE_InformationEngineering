#ifndef PDADD_H_
#define PDADD_H_
#include "DiaryBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class pdadd : public DiaryBase
{
public:
    pdadd();
    virtual ~pdadd();

private:
    string read(int *, int *, int *);
};

pdadd::pdadd()
{
    this->ReadFile();

    OneDiary d;
    d.content = read(&d.year, &d.month, &d.day);

    istringstream sin(d.content);
    sin>>d.title;

    this->DeleteByTime(d.year, d.month, d.day);
    diary.push_back(d);
}

pdadd::~pdadd()
{

}

string pdadd::read(int * dYear, int * dMonth, int * dDay)
{
    string str;
    string total;

    cin>>*dMonth>>*dDay>>*dYear;


    while (cin>>str)
    {
        if (str == ".")
            break;
        total += ' ' + str;
    }
    return total;
}

#endif // PDADD_H_
