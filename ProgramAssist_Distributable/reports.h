#pragma once
#include"reportStarter.h"
#include"includes.h"
#define VALID_REPORT_ARGS std::size(valid_commands)
#define COLS 3

short int properFileOpen(std::string);
int reporter();

class reportkeeper {
	std::string* report_names, * report_records;		//call delete[] on these variables everytime they are unloaded.
	float* workTime;
	int rno;
	std::ofstream filewrite;
	std::ifstream fileread;
	char* buffer;
	void initTimer();

public:
	reportkeeper();
	void initialize();										// refreshes/stores memory into the corresponding variables
	void newReport(char* reportName, char* reportRecord);	//writes old data along with new data into the file.
	void updateReport(char* reportName, char* reportRecord);
	void displayReports();
	void deleteReport(char* reportName);
	void timekeeper(int);
	~reportkeeper()
	{
		filewrite.close();
		delete[] buffer;
		delete[] report_records;
		delete[] report_names;
		delete[] workTime;
	}
};

