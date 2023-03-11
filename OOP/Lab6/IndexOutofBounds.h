#ifndef INDEX_OUTOF_BOUNDS_H_
#define INDEX_OUTOF_BOUNDS_H_
#include <string>
using std::string;

class IndexOutofBounds{
private:
	string msg;
public:
	IndexOutofBounds(string s);
	string what();
};

#endif
