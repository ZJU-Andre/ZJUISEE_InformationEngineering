#ifndef PDLIST_H_
#define PDLIST_H_
#include "DiaryBase.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class pdlist : public DiaryBase
{
public:
	pdlist(int, char **);
	void InitCmd(int, char **);
private:
	int preYear, preMonth, preDay;
	int nowYear, nowMonth, nowDay;
	int ParseInt(char *);
	void print(vector <OneDiary> :: iterator);
	void list();
};

pdlist::pdlist(int argc, char ** argv)
{
	this->ReadFile();
	this->InitCmd(argc, argv);
	this->list();
}

void pdlist::InitCmd(int argc, char ** argv)
{
	if (argc < 6)
		return;
	preMonth 	= ParseInt(argv[1]);
	preDay 		= ParseInt(argv[2]);
	preYear 	= ParseInt(argv[3]);
	nowMonth    = ParseInt(argv[4]);
	nowDay 		= ParseInt(argv[5]);
	nowYear		= ParseInt(argv[6]);
}

int pdlist::ParseInt(char * s)
{
	int temp;
	string str(s);
	istringstream sin(str);
	sin>>temp;
	return temp;
}

void pdlist::list()
{
	for(vector<OneDiary> :: iterator ai = diary.begin(); ai != diary.end(); ++ai)
	{
		if (ai->year >= preYear && ai->year <= nowYear && ai->month >= preMonth && ai->month <= nowMonth && ai->day >= preDay && ai->day <= nowDay)
			print(ai);
	}
}

void pdlist::print(vector <OneDiary> :: iterator ai)
{
	cout<<"Date(MM/DD/YYYY):" << ai->month << ' ' << ai->day << ' ' << ai->year << endl;
	cout<<"Title:\t" << ai->title << endl;
	cout<<"Content:\t" << ai->content << endl;
}

#endif