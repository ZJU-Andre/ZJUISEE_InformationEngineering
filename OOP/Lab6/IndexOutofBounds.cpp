#include "IndexOutofBounds.h"

IndexOutofBounds::IndexOutofBounds(string err)
{
	msg = err;
}

string IndexOutofBounds::what()
{
	return msg;
}
