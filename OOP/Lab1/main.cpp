#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct  student{
	string str;
	int score[3];
}S;

int main ( )
{

	S s[10];

	int sum1[3] = {0};
	int i, j;

	ifstream in1;
	in1.open( "student name.txt" );
	if( !in1 )
		cout << "error" << endl;
	for( i = 0; i < 10; i++ )
		in1 >> s[i].str;

	ifstream in2;
	in2.open( "score1.txt" );
	if( !in2 )
		cout << "error" << endl;
	for( i = 0; i < 10; i++ ){
		in2 >> s[i].score[0];
		sum1[0] += s[i].score[0];
	}

	ifstream in3;
	in3.open( "score2.txt" );
	if( !in3 )
		cout << "error" << endl;
	for( i = 0; i < 10; i++ ){
		in3 >> s[i].score[1];
		sum1[1] += s[i].score[1];
	}

	ifstream in4;
	in4.open( "score3.txt" );
	if( !in4 )
		cout << "error" << endl;
	for( i = 0; i < 10; i++ ){
		in4 >> s[i].score[2];
		sum1[2] += s[i].score[2];
	}

	int sum2[10] = {0};

	for( i = 0; i < 10; i++ )
		sum2[i] += ( s[i].score[0] + s[i].score[1] + s[i].score[2] ) ;

	float aver1[3], aver2[10];
	for( i = 0; i < 3; i++ )
		aver1[i] = sum1[i] / 10.0;
	for( i = 0; i < 10; i++ )
		aver2[i] = sum2[i] / 3.0;

	cout << "no\t" << "name\t" << "score1\t";
	cout << "score2\t" << "score3\t" << "average\t" << endl;

	for( i = 0; i < 10; i++ ){
		cout << i + 1 << "\t" << s[i].str << "\t";
		cout << s[i].score[0] << "\t" << s[i].score[1] << "\t";
		cout << s[i].score[2] << "\t" << aver2[i] << "\t" << endl;
	}

	cout << "\t" << "average\t";
	for( i = 0; i < 3; i++ )
		cout << aver1[i] << "\t";
	cout << endl;

	int min[3], max[3];
	for( i = 0; i< 3; i++ ){
		max[i] = 0;
		min[i] = s[0].score[i];
		for( j = 0; j < 10; j++ ){
			if( s[j].score[i] > max[i] )
				max[i] = s[j].score[i];
			if( s[j].score[i] < min[i] )
				min[i] = s[j].score[i];
		}
	}

	cout << "\t" << "min\t";
	for( i = 0; i < 3; i++ )
		cout << min[i] << "\t";
	cout << endl;

	cout << "\t" << "max\t";
	for( i = 0; i < 3; i++ )
		cout << max[i] << "\t";

	return 0;
}
