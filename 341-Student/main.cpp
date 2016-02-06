//
//C++ program to compute student exam averages.
//
//<<FAYAZ KHAN>>
//U. of Iillinois, Chicago
//CS341, Fall 2015
//Homework 2
//


/*
We have to leave off from here but we got it to iterate through the file no problem 
but it is creating the obeject and using the push_back but i found a video that maybe able to 
help c++ tutorial 21-vector of job -programinghelporg

once the push_back is done all the rest of the stuff.should hopefully not be a problem
*/
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

class student
{
	public://access specifier this allow int main() access to everything 
		string  NetID;
		int UIN;
		int exam1;
		int exam2;
		int exam3;
		double avgExam;

		student(string netid, int uin, double ex1, double ex2, double ex3)//this is a constructor notice this is the same name as the class		
		{
			/*
			Main purpose of a constructor is to give them an initial value
			*/
			NetID = netid;
			UIN = uin;
			exam1 = ex1;
			exam2 = ex2;
			exam3 = ex3;
			avgExam = (ex1 + ex2 + ex3) / 3;

			//cout << "We have a new student "<<NetID<<"  "<<avgExam<<"\n"; 
		}
		
};

void fillClass(vector <student>& sVData);//treat it like an array. The & will reflect changes
//& you are passing by reference meaning you are not making a copy 

void printExamAvg(vector <student>& sVData);
void printNetID(vector <student>& sVData);
void printUIN(vector <student>& sVData);

int main()
{ 
	/*The class student is created but we have to have a way of access student. We need to 
	create an object of student because this allows us to access student 
	ex student padawan
	*/
	vector <student> sVData;

	fillClass(sVData);
	printExamAvg(sVData);
	printNetID(sVData);
	printUIN(sVData);

	system("PAUSE");
	return 0;
}

/*
string  NetID;
int UIN;
int exam1;
int exam2;
int exam3;
double avgExam;
*/

void printUIN(vector <student>& sVData)
{
	sort(sVData.begin(), sVData.end(), [](student const &e1, student const &e2){return e1.UIN < e2.UIN; });

	cout << "By NetID:\n";
	for (auto i = sVData.begin(); i != sVData.end(); ++i)
		cout << " " << (*i).UIN << ": avg = " << (*i).avgExam << " based on exams " << (*i).exam1 << ", " << (*i).exam2 << ", " << (*i).exam3 << "\n";
	cout << "\n";
}

void printNetID(vector <student>& sVData)
{
	sort(sVData.begin(), sVData.end(), [](student const &e1, student const &e2){return e1.NetID < e2.NetID; });

	cout << "By NetID:\n";
	for (auto i = sVData.begin(); i != sVData.end(); ++i)
		cout << " " << (*i).NetID << ": avg = " << (*i).avgExam << " based on exams " << (*i).exam1 << ", " << (*i).exam2 << ", " << (*i).exam3 << "\n";
	cout << "\n";
}

void printExamAvg(vector <student>& sVData)
{
	sort(sVData.begin(), sVData.end(), [](student const &e1, student const &e2){return e1.avgExam > e2.avgExam; });

	cout << "By exam average:\n";
	for (auto i = sVData.begin(); i != sVData.end(); ++i)
		cout << " " << (*i).NetID << ": avg = " << (*i).avgExam << " based on exams " << (*i).exam1 << ", " << (*i).exam2 << ", " <<(*i).exam3 << "\n";
	cout << "\n";
}


void fillClass(vector <student>& sVData)
{
	ifstream file("students.txt");
	istream_iterator<string> start(file), end;

	int index = 0;
	string netid;
	string uin;
	string exam1, exam2, exam3;

	for (auto iter = start; iter != end; ++iter)
	{
		netid = *iter;
		++iter;
		uin = *iter;
		++iter;
		exam1 = *iter;
		++iter;
		exam2 = *iter;
		++iter;
		exam3 = *iter;
	
		student s(netid, atoi(uin.c_str()),atoi(exam1.c_str()),atoi(exam2.c_str()),atoi(exam3.c_str()));
		sVData.push_back(s);
		
	}
}
