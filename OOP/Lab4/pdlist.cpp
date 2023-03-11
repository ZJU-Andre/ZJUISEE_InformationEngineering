#include "DiaryBase.h"
#include "pdlist.h"
using namespace std;

int main(int argc, char ** argv)
{
	DiaryBase * base = new pdlist(argc, argv);
	delete base;
	return 0;
}