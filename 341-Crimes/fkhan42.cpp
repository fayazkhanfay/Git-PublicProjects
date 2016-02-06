//
//C++ program to analyze Chicago crime data
//<<FAYAZ KHAN>>
//U. of Illinois, Chicago
//CS341 , Fall 2015
//Homework 3
//


#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>
using namespace std;

class Communities // this object consist of data from Communities.csv
{
public:
	int Number;
	string Community;

	Communities(int number, string community)
	{
		Number = number;
		Community = community;

		//cout << "We have a new com : " << Number << " & " << Community << "\n";

	}

};

class IUCR //this object consist data from IUCR-codes.csv
{

public:
	string iucr;
	string primDes;
	string secDes;
	int count;//not from file but updated from a funnton compared to big crimes list file 
	int Top5count;

	IUCR(string IUcr, string pDes, string sDes)
	{
		iucr = IUcr;
		primDes = pDes;
		secDes = sDes;
		count = 0;
		Top5count = 0;
		//cout << "new:: " << iucr << " " << primDes << " " << secDes<< "\n";
	}
};


class Crimes//this object consist data from Crimes-2014-2015.csv
{
public:
	string IUCR_Numb;
	int community;
	int Year;

	/*
	The commented out variables are irrelevant data that will be not used. 
	*/


	//string Arrest;
	//string Domestic;
	//string Beat;
	//int District;
	//int Ward;
	//string Date;

	//Crimes(string date, string IUCR_numb, string arrest, string domestic, string beat, int district,
	//int ward, int comm, int year)

	Crimes(string IUCR_numb, int comm, int year)
	{
		IUCR_Numb = IUCR_numb;
		community = comm;
		Year = year;

		//Arrest = arrest;
		//Domestic = domestic;
		//Beat = beat;
		//District = district;
		//Ward = ward;
		//Date = date;

		//cout << "newCrimes: " << Date << " " << IUCR_Numb << " " << Arrest << " " << Domestic << " " << Beat << " " <<
		//District << " " << Ward << " " << community << " " << Year << "\n";
		//cout << "smallCrimes: " << IUCR_Numb << " , " << community << " , " << Year << "\n";
	}

};



/*Below 3 functions fill the objects, display and do counting   */
void fillComm(vector <Communities>& comm);
void fill_IUCR(vector <IUCR>& iucr);
int fillCrimes(vector <Crimes>& crime, vector <IUCR>& iucr, int *maxDate, int *minDate);//More details in function

/*Not Self written the sort function, using containers and using lambda function*/
void sortCrimes(vector<Crimes>& crime);
void sortIUCR(vector <IUCR>& code);

/*This is for testing, to see if everything works correct but also a good of 
using a for loop to iterate through data*/
void printCrimes(vector<Crimes>& crime);
void print_IUCR(vector<IUCR>& iucr);


void UserCrimeCode(vector<IUCR>& code, int count, int maxDate, int minDate, vector<Crimes>& crime);
/*UserCrimeCode: asks the user to enter a crime code and display  stats based on the crime code*/

void DispTopTen(vector<IUCR>& code);
/*DispTopTen : displays  the top ten based on the frequency of crime */

void UserComm(vector<IUCR>& code, int count, vector<Communities>& comm, vector<Crimes>& crime);
/*UserComm: asks the user to enter a community and displays stats on the community */

/*Below function parses the csv and sets up the relevant data to be use in the object*/
Communities ParseComm(string line);
IUCR Parse_IUCR(string line);
Crimes ParseCrimes(string line);

int main()
{

	vector <Communities> comm;
	vector <IUCR> iucr;
	vector <Crimes> crime;

	crime.reserve(1000000);
	int maxDate = 0;
	int minDate = 3000;

	fill_IUCR(iucr);//HAS TO BE BEFORE FILL CRIMES !!!
	int count = fillCrimes(crime, iucr, &maxDate, &minDate);
	fillComm(comm);

	sortCrimes(crime);
	//printCrimes(crime);
	//print_IUCR(iucr);
	sortIUCR(iucr);
	//print_IUCR(iucr);

	DispTopTen(iucr); //first screen shot from hw3.pdf
	UserComm(iucr, count, comm, crime);
	UserCrimeCode(iucr, count, maxDate, minDate, crime);//third screen shot from hw3.pdf
	
	//system("PAUSE");
}

void UserComm(vector<IUCR>& code, int count, vector<Communities>& comm, vector<Crimes>& crime)
{
	cout << ">> By Community <<\n\n";

	int UserCode = -999;
	/*int Number;
	string Community;*/
	do
	{
		if (UserCode != -999)
		{
			if (UserCode >= 1 && UserCode <= 77)
			{
				cout << ">> " << comm[UserCode-1].Community << " <<\n";


				/*string IUCR_Numb;
				int community;
				int Year;*/

				/*This counts how many times the community has a crime in the crimes object*/
				int commCount = count_if(crime.begin(), crime.end(), [&](Crimes const &e1)
				{
					if (e1.community == UserCode)
						return true;
					else
						return false;
				});

				cout << ">> Total:\t" << commCount << "\n";
				//cout << ">> Percentage: " << (((*codeSpot).count / (double)count))*100 << "%\n";
				cout << ">> Percentage:  " << (commCount / (double)count) * 100 << "%\n";

				int homiCount = count_if(crime.begin(), crime.end(), [&](Crimes const &e1)
				{
					string tempCompare = e1.IUCR_Numb;//so it does not constantly keep on referencing same
														//unnessarly repeatadly 

					//I am doing string comparison because i dont want to convert to int because some of them
					//have letters in them. This is why I am doing string comparisons
					if ((e1.community == UserCode)&&(tempCompare == "0110"||tempCompare == "0130"||
						tempCompare == "0141"||tempCompare== "0142"))
						return true;
					else
						return false;

				});

				cout << ">> Homicides:\t" << homiCount << "\n";

				cout << ">> Top-5 Crimes <<\n";
				cout << "Rank\tIUCR\tNumber\tDescription \n";

				for (auto iter = crime.begin(); iter != crime.end(); ++iter)
				{
					if ((*iter).community == UserCode)
					{
						auto codeFind = find_if(code.begin(), code.end(), [&](IUCR const &e1)
						{
							if (e1.iucr == (*iter).IUCR_Numb)
								return true;
							else
								return false;
						});

						if (codeFind != code.end())
							((*codeFind).Top5count)++;

					}

				}


				sort(code.begin(), code.end(), [](IUCR const &e1, IUCR const &e2)
				{
					return e1.Top5count > e2.Top5count;
				});

				int printFive = 0;

				while (printFive < 5)
				{
					cout << printFive + 1 << ".\t" << code[printFive].iucr << "\t" << code[printFive].Top5count <<
						"\t" << code[printFive].primDes << " (" << code[printFive].secDes << ")\n";
					printFive++;
				}

				cout << "\n";
			}
			else
			{
				cout << "** Invalid community number, please try again... \n\n";
			}
		}

		cout << "Please enter a community number [1..77], 0 to stop: ";
		cin >> UserCode;
	} while (UserCode != 0);

	cout << "\n";
}




void DispTopTen(vector<IUCR>& code)
{
	/*string iucr;
	string primDes;
	string secDes;
	int count;*/
	cout << ">> TOP-10 Crimes <<\n";
	cout << "Rank\t IUCR\t Number\t Description \n";

	int i = 0;

	while (i < 10)
	{
		cout << (i+1) << ".\t " << code[i].iucr << "\t " << code[i].count << "\t " << code[i].primDes << " ("
			<< code[i].secDes << ")\n";
		i++;
	}
	

	cout << "\n\n";
}

void sortIUCR(vector <IUCR>& code)
{
	sort(code.begin(), code.end(), [](IUCR const &e1, IUCR const &e2){return e1.count > e2.count; });
}

void print_IUCR(vector<IUCR>& iucr)
{
	/*
	string iucr;
	string primDes;
	string secDes;
	int count;
	*/

	int i = 0;
	for (auto iter = iucr.begin(); iter != iucr.end(); ++iter)
	{
		if ((*iter).count>0)
			cout << "print_iucr:: " << (*iter).iucr << "," << (*iter).count << "\n";
		i++;

		/*if (i == 10)
		system("PAUSE");*/
	}

}

void UserCrimeCode(vector<IUCR>& code, int count, int maxDate, int minDate, vector<Crimes>& crime)
{
	cout << ">> By IUCR Crime Code <<" << "\n\n";
	string UserCode = "0000";
	int tempMax;

	do
	{

		if (UserCode != "0000")
		{
			auto codeSpot = find_if(code.begin(), code.end(), [&](IUCR const &e1){return e1.iucr == UserCode;  });

			if (codeSpot != code.end())
			{
				cout << ">> " << (*codeSpot).primDes << " (" << (*codeSpot).secDes << ")\n";
				cout << ">> Total: \t" << (*codeSpot).count << "\n";
				cout << ">> Percentage: " << (((*codeSpot).count / (double)count))*100 << "%\n";
				cout << ">> By Year:\n";

				while (tempMax >= minDate)
				{
					//find_if(iucr.begin(), iucr.end(), [&](IUCR const &e1){return e1.iucr == temp.IUCR_Numb;  });
					auto majorCount = count_if(crime.begin(), crime.end(), [&](Crimes const &e1)
					{
						if ((e1.IUCR_Numb == UserCode) && (e1.Year == tempMax))
							return true;
						else
							return false;
					});
					cout << "\t" << tempMax << ": " << majorCount << "\n";
					tempMax--;
				}
				cout << "\n";
			}
			else
			{
				cout << "** Invalid IUCR code, please try again...\n\n";
			}

		}
		cout << "Please enter an IUCR crime code [e.g. 0110 or 031A], 0000 to stop: ";
		cin >> UserCode;
		cout << "\n";

		tempMax = maxDate;// this for printing in the while loop and decrements from their in loop, this resets it

	} while (UserCode != "0000");

	cout << "\n>> DONE! <<\n\n\n";
}

void printCrimes(vector<Crimes>& crime)
{
	for (auto iter = crime.begin(); iter != crime.end(); ++iter)
		cout << "SortTest:: " << (*iter).IUCR_Numb << "," << (*iter).community << "," << (*iter).Year << "\n";
}

void sortCrimes(vector<Crimes>& crime)
{
	sort(crime.begin(), crime.end(), [](Crimes const &e1, Crimes const &e2){return e1.IUCR_Numb < e2.IUCR_Numb; });
}

Crimes ParseCrimes(string line)
{
	istringstream strstream(line);

	string Date;
	string IUCR_Numb;
	string Arrest;
	string Domestic;
	string Beat;
	string District;
	string  Ward;
	string community;
	string Year;

	int yearInt;
	int commInt;

	std::getline(strstream, Date, ',');
	std::getline(strstream, IUCR_Numb, ',');
	std::getline(strstream, Arrest, ',');
	std::getline(strstream, Domestic, ',');
	std::getline(strstream, Beat, ',');
	std::getline(strstream, District, ',');
	std::getline(strstream, Ward, ',');
	std::getline(strstream, community, ',');
	std::getline(strstream, Year, ' ');


	try
	{
		yearInt = std::stoi(Year);
	}
	catch (...)
	{
		yearInt = -1;
	}

	try
	{
		commInt = std::stoi(community);
	}
	catch (...)
	{
		commInt = -1;
	}



	//cout << "BIGCRIMES: " << Date << "," << IUCR_Numb << "," << Arrest << "," << Domestic << "," << Beat << "," <<
	//District << "," << Ward << "," << community << "," << Year << "\n";


	return Crimes(IUCR_Numb, commInt, yearInt);
}

int fillCrimes(vector <Crimes>& crime, vector <IUCR>& iucr, int *maxDate, int *minDate)
{
	/*
	string IUCR_Numb;
	int community;
	int Year;
	*/

	/*While iteratting the .csv file it is also gathering stats on the totol frequency of crimes 
	and also freuquncey of crimes for the individual crime code but storng it in the iucr.count object*/
	ifstream file("Crimes-2014-2015.csv");
	string line;

	cout << ">> Reading crime data 'Crimes-2014-2015.csv'... ";

	int count = 0;

	std::getline(file, line);
	while (std::getline(file, line))
	{
		Crimes temp = ParseCrimes(line); //I did this because i need to extract some data from object before push_back 

		//cout << "compare:: " << temp.IUCR_Numb << "\n";

		//look through the iucr code object matches the code and crimes and returns to the pointer to the location
		auto codeSpot = find_if(iucr.begin(), iucr.end(), [&](IUCR const &e1){return e1.iucr == temp.IUCR_Numb;  });


		/*if found it will increment count on iucr.count*/
		if (codeSpot != iucr.end())
		{
			//cout << "count this :: " << (*codeSpot).count << "\n";
			//system("PAUSE");
			((*codeSpot).count)++;//this is iucr object 
		}


		if (temp.Year > *maxDate)//this varaibale was created in main i wanted to know the max and min year in crimes
			*maxDate = temp.Year;
		if (temp.Year < *minDate)
			*minDate = temp.Year;

		crime.push_back(temp); //now pushes object into vector 

		count++;
	}

	cout << "[" << crime.size() << "]\n";
	cout << ">> Reading IUCR codes 'IUCR-codes.csv'... ";//I need to keep the display in oder but I cannot rearrange the 
		//function in main because they are dependedent of each other. This is the next best solution 
	cout << "[" << iucr.size() << "]\n";
	return count;
}

void fill_IUCR(vector <IUCR>& iucr)
{
	ifstream file("IUCR-codes.csv");
	string line;

	//cout << ">> Reading IUCR codes 'IUCR-codes.csv'... ";

	std::getline(file, line);//gets rid of the first line of csv file 

	while (std::getline(file, line))
		iucr.push_back(Parse_IUCR(line));

	//cout << "[" << iucr.size() << "]\n";
}

IUCR Parse_IUCR(string line)
{
	istringstream strstream(line);
	string iucr, primDes, secDes;

	std::getline(strstream, iucr, ',');
	std::getline(strstream, primDes, ',');
	std::getline(strstream, secDes);

	return IUCR(iucr, primDes, secDes);
}

Communities ParseComm(string line)
{
	istringstream strstream(line);
	string number, community;

	std::getline(strstream, number, ',');
	std::getline(strstream, community, ' ');

	int Number = std::stoi(number);

	return Communities(Number, community);

}

void fillComm(vector <Communities>& comm)
{
	ifstream file("Communities.csv");
	string line;

	cout << ">> Reading communities file 'Communities.csv'... ";

	std::getline(file, line);//gets rid of the first line of csv file 

	while (std::getline(file, line))
		comm.push_back(ParseComm(line));

	cout << "[" << comm.size() << "]\n\n";

}
