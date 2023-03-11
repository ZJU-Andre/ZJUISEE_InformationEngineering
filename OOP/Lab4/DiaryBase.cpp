#include "DiaryBase.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool OneDiarySort(OneDiary a, OneDiary b)
{
	return (a.year != b.year ? a.year > b.year : (a.month != b.month ? a.month > b.month : (a.day != b.day ? a.day > b.day : 0)));
}
void DiaryBase::ReadFile()
{
	fileName = "data";
	ifstream fin(fileName.c_str());

	OneDiary d;
	while (fin>>d.month>>d.day>>d.year>>d.title)
	{
		getline(fin, d.content);
		d.title 	= d.title.substr(d.title.find_first_not_of(" \t"), d.title.find_last_not_of(" \t"));
		d.content 	= d.content.substr(d.content.find_first_not_of(" \t"), d.content.find_last_not_of(" \t"));
		diary.push_back(d);
	}

	fin.close();
}

void DiaryBase::SaveFile()
{
	sort(diary.begin(), diary.end(), OneDiarySort);
	ofstream fout(fileName.c_str());
	for(vector<OneDiary> :: iterator ai = diary.begin(); ai != diary.end(); ++ai)
	{
		fout<<ai->month<<' '<<ai->day<<' '<<ai->year<<' '<<ai->title<<' '<<ai->content<<endl;
	}
	fout.close();
}

bool DiaryBase::DeleteByTime(int year, int month, int day)
{
	// cout<<diary.size()<<endl;
	for(vector<OneDiary> :: iterator ai = diary.begin(); ai != diary.end();)
	{
		// cout<<ai->year<<'\t'<<ai->month<<'\t'<<ai->day<<endl;
		if (year == ai->year && month == ai->month && day == ai->day){
			// cout<<ai - diary.begin()<<endl;
			ai = diary.erase(ai);
			return true;
		} else {
			++ai;
		}
	}
	return false;
}

DiaryBase::~DiaryBase()
{
	SaveFile();
}