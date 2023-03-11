#ifndef PDSHOW_H_
#define PDSHOW_H_
#include "DiaryBase.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class pdshow : public DiaryBase
{
private:
	void print();
	int year, month, day;
public:
	pdshow();
	~pdshow(){};
};

pdshow::pdshow()
{
	this->ReadFile();
	cin>>month>>day>>year;
	print();
}

void pdshow::print()
{
	for (vector <OneDiary> :: iterator ai = diary.begin(); ai != diary.end(); ++ai)
	{
		if (ai->year == year && ai->month == month && ai->day == day)
		{
			cout<<"Date(MM/DD/YYYY):" << month << ' ' << day << ' ' << year << endl;
			cout<<"Title:\t" << ai->title << endl;
			cout<<"Content:\t" << ai->content << endl;
			return ;
		}
	}
	cout<<"There is no diary that day!";
}

#endif