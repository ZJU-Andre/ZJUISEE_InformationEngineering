#ifndef DIARY_BASE_H_
#define DIARY_BASE_H_
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct OneDiary{
	int year, month, day;
	string title, content;
};

class DiaryBase
{
protected:
    string fileName;
	vector<OneDiary> diary;
	void ReadFile();
	void SaveFile();
	bool DeleteByTime(int, int, int);
public:
	DiaryBase(){};
	virtual ~DiaryBase();
};

#endif
