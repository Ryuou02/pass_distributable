#pragma once
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include "includes.h"

//start Codes --
#define NOSTART 0
#define WITHSTART 1
#define PROGRAMS PASSDIR "report_programs\\"
#define OPENALL "openalltemplate"

#define ASK_UPDATE std::cin >> c;\
if(c == 'y' || c == 'Y') updateReport();

class reportStarter
{
	std::string reportName;
	std::string usefulString;
	char c, useful_c[300];
	std::string reportPath;
	std::string openallPath;
	std::string startitPath;
	std::ofstream filewrite;
	std::ifstream fileread;
public:
	//open program is constructor
	reportStarter() { FATAL_ERROR("there is no default constructor for reportStarter") }
	reportStarter(std::string report_name, int stCode);
	//close is destructor
	~reportStarter();
	void createFile();
	void updateReport();
	void makeOpenFile();
	void log(char* text, double ct);
	void checklog();
};