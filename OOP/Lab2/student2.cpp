#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<stdlib.h>

using namespace std;


struct stu {
	string name;
	string course[9];
	float score[9];
};

int sum = 0;  //record the number of all the student which had been input;
vector<float> average(9, 0); //record the average score of the total nine courses;
vector<int> maxm(9, 0);    //record the highest score of the total nine courses;
vector<int> minm(9, 0);    //record the lowest score of the total nine courses;
vector<int> Num(9, 0);    //record the number of students who picked each course;
// we set nine courses totally, and each course has its order;
// Chinese - 0; Math - 1; English - 2; Physics - 3; Chemistry - 4; Biology - 5; History - 6; Politics - 7; Geography - 8;

int Judge(string course) {       //to judge which course the student takes and return the this course's number;
	int order = -1;
	if (course == "Chinese") {
		order = 0;
	}
	if (course == "Math") {
		order = 1;

	}
	if (course == "English") {
		order = 2;

	}
	if (course == "Physics") {
		order = 3;
	}
	if (course == "Chemistry") {
		order = 4;
	}
	if (course == "Biology") {
		order = 5;
	}
	if (course == "History") {
		order = 6;
	}
	if (course == "Politics") {
		order = 7;
	}
	if (course == "Geography") {
		order = 8;
	}
	Num[order] = Num[order]+1;    //the total number of students who take this course need to be added;
	return order;
}

int main() {
	int i, j;
	stu student;
	string output[100][100];   //to preserve the whole results which need to be output;


	for (i = 0; i < 10000; i++) {
		float total = 0;  //count the number of the students courses;
		float SumScore = 0;   //calculate the total scores of the student gets;
		cin >> student.name;
		if (student.name != "%") {   // the whole input ends up with '%';
			output[i][0] = to_string(i); //change the type of 'i' to make it preserve in the final output as string;
			output[i][1] = student.name; //preserve the name of student in the final output;
			sum++;
			for (j = 0; j < 1000; j++) {
				cin >> student.course[j];
				if (student.course[j] != "%") {   //each student's information ends up with '%';
					total = total + 1;      //this student's course need to be added;
					int courseNum = Judge(student.course[j]);//judge which course is it;
					cin >> student.score[j];
					int sco = student.score[j];  //change the type of the score;
					if (maxm[courseNum] == 0) {   //find the highest score of this course;
						maxm[courseNum] = sco;
					}
					else if (student.score[j] > maxm[courseNum]) {
                        maxm[courseNum] = sco;
					}
					if (minm[courseNum] == 0) {    //find the lowest score of this course;
						minm[courseNum] = sco;
					}
					else if (student.score[j] < minm[courseNum]) {
                        minm[courseNum] = sco;
					}
					SumScore += student.score[j];  //calculate the total score this student gets;
					average[courseNum] += student.score[j]; //calculate the total score of this course;
					output[i][courseNum + 2] = to_string(sco); //change the type of sco and put it into the final output as string;
				}
				else
					break;
			}

			float average = SumScore / total;  //calculate the average score of this course;
			output[i][11] = to_string(average);  //change the type of average and put it into the final output as string;
		}
		else
			break;
	}
	for (i = 0; i < 9; i++) {
		if(average[i]!=0)
		average[i] = average[i] / Num[i];   //calculate the average of each course;
	}
	for (i = 0; i < sum; i++) {
		for (j = 2; j < 11; j++) {
			if (output[i][j].empty()) {
				output[i][j] = "/";         //fill the blanks which students does not take;
			}
		}
	}
	cout << "no   name    Chinese   Math     English   Physics   Chemistry   Biology   History   Politics   Geography   average" << endl;

	for (i = 0; i < sum; i++) {    //output the students' information ;
		cout << setw(5) << setfill(' ') << left<<output[i][0];
		cout << setw(8) << setfill(' ') <<left<< output[i][1];
		cout << setw(10) << setfill(' ') <<left<< output[i][2];
		cout << setw(9) << setfill(' ') << left<<output[i][3];
		cout << setw(10) << setfill(' ') <<left<< output[i][4];
		cout << setw(10) << setfill(' ') << left<<output[i][5];
		cout << setw(12) << setfill(' ') <<left<< output[i][6];
		cout << setw(10) << setfill(' ') << left<<output[i][7];
		cout << setw(10) << setfill(' ') << left<<output[i][8];
		cout << setw(11) << setfill(' ') << left<<output[i][9];
		cout << setw(12) << setfill(' ') << left<<output[i][10];
		cout << output[i][11]<<endl;
	}

	cout << "    Average  ";      //output each course's average score;
	cout << setw(10) << setfill(' ') << left << fixed << setprecision(1) << average[0];
	cout << setw(9) << setfill(' ') << left << fixed << setprecision(1) << average[1];
	cout << setw(10) << setfill(' ') << left << fixed << setprecision(1) << average[2];
	cout << setw(10) << setfill(' ') << left << fixed << setprecision(1) << average[3];
	cout << setw(12) << setfill(' ') << left << fixed << setprecision(1) << average[4];
	cout << setw(10) << setfill(' ') << left << fixed << setprecision(1) << average[5];
	cout << setw(10) << setfill(' ') << left << fixed << setprecision(1) << average[6];
	cout << setw(11) << setfill(' ') << left << fixed << setprecision(1) << average[7];
	cout << average[8] << endl;

	cout << "    Max      "; // output each course's highest score;
	cout << setw(10) << setfill(' ') << left << maxm[0];
	cout << setw(9) << setfill(' ') << left << maxm[1];
	cout << setw(10) << setfill(' ') << left << maxm[2];
	cout << setw(10) << setfill(' ') << left << maxm[3];
	cout << setw(12) << setfill(' ') << left << maxm[4];
	cout << setw(10) << setfill(' ') << left << maxm[5];
	cout << setw(10) << setfill(' ') << left << maxm[6];
	cout << setw(11) << setfill(' ') << left << maxm[7];
	cout << maxm[8] << endl;

	cout << "    Min      "; // output each course's lowest score;
	cout << setw(10) << setfill(' ') << left << minm[0];
	cout << setw(9) << setfill(' ') << left << minm[1];
	cout << setw(10) << setfill(' ') << left << minm[2];
	cout << setw(10) << setfill(' ') << left << minm[3];
	cout << setw(12) << setfill(' ') << left << minm[4];
	cout << setw(10) << setfill(' ') << left << minm[5];
	cout << setw(10) << setfill(' ') << left << minm[6];
	cout << setw(11) << setfill(' ') << left << minm[7];
	cout << minm[8] << endl;
    system("pause");
	return 0;

}
