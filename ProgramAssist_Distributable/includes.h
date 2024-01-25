#pragma once
#include<string.h>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include"colorCodes.h"
#include"definitions.h"

#define SPACE(K)	for (int i = 0; i < K; i++)	std::cout.put(K);
#define COLSIZE 40
#define DRAWLINE std::cout.put(ld);\
for (int i = 0; i < colNum; i++){\
	for (int i = 0; i < COLSIZE; i++)\
		std::cout.put(l);\
	std::cout.put(ld);\
}std::cout.put('\n');

inline int safeCommandExec(std::string command)
{
	int k;
	std::ifstream fileread;
	command = "(" + command + ") && (echo 0 > tmp) || (echo 1 > tmp)";
	system(command.c_str());
	fileread.open("tmp");
	fileread >> k;
	fileread.close();
	return k;
}
inline int openProgram(char* program_name)
{
	const std::string storage_file = PROGRAM_FILE;

	int pc;
	char a;
	char* shit;
	std::string* pname, * pdir, rpname = program_name;
	std::ifstream fileread;
	std::ofstream filewrite;

	fileread.open(storage_file);
	if (fileread.fail())
	{
		filewrite.open(storage_file);
		filewrite << 0 << "\n";
		filewrite.close();
		fileread.open(storage_file);
		if (fileread.fail())
		{
			std::cout << "PLEASE STOP DELETING PROGRAM FILES!!";
			exit(0);
		}
	}

	shit = new char[1000];

	fileread >> pc;			//pc contains integer value of number of programs in the file.
	fileread.get();
	pname = new std::string[pc];
	pdir = new std::string[pc];
	for (int i = 0; i < pc; i++)
	{
		if (fileread.eof() && i == pc)
		{
			std::cout << "###FATAL ERROR : SOMETHINGWENT WRONG, SYSTEM'S ABOUT TO EXPLODE!!!####";
			exit(0);
		}
		fileread.getline(shit, 1000);	//get program name
		pname[i] = shit;
		std::cout << "\n program name:" << shit;
		fileread.getline(shit, 1000);	//get program directory
		pdir[i] = shit;
		std::cout << "\n program directory:" << shit;
		if (pname[i] == rpname) {
			system(shit);
			return 0;
		}
	}
	fileread.close();


	//--------------------------------- IN CASE OF NEW PROGRAM --------------------------------------------

	std::cout << "\nis this a new program(Y/N)";
	a = std::cin.get();
	if (a == 'Y' || a == 'y') {
		filewrite.open(storage_file);
		filewrite << pc + 1;
		filewrite.put('\n');
		for (int i = 0; i < pc; i++)
		{
			filewrite << pname[i] << "\n";
			filewrite << pdir[i] << "\n";
		}
		filewrite << rpname << "\n";
		std::cout << "\nenter directory of file : ";
		std::cin.get();
		std::cin.getline(shit, 1000);
		rpname = shit;
		filewrite << rpname << "\n";

		filewrite.close();
	}
	else
		std::cout << "the program wasn't found in list of available programs.";
	delete[] shit;
	return 1;
}
inline void updatePrograms(char* pname, char* pdir)		//used to update list of programs, i.e. program_list file
{
	std::string pn = pname, pd = pdir;
	std::string* programs, * pdirs;
	char buffer[1000];
	std::ifstream fileread;
	std::ofstream filewrite;
	int pno;

	fileread.open(PROGRAM_FILE);
	fileread >> pno;
	fileread.get();
	programs = new std::string[pno];
	pdirs = new std::string[pno];
	for (int i = 0; i < pno; i++) {
		fileread.getline(buffer, 1000);
		programs[i] = buffer;
		fileread.getline(buffer, 1000);
		pdirs[i] = buffer;
	}
	fileread.close();
	filewrite.open(PROGRAM_FILE);
	filewrite << pno;
	filewrite.put('\n');
	for (int i = 0; i < pno; i++) {
		if (programs[i] != pn)
		{
			filewrite << programs[i] << '\n';
			filewrite << pdirs[i] << '\n';
		}
		else {
			filewrite << programs[i] << '\n';
			filewrite << pd << '\n';
		}
	}
	filewrite.close();
}
inline void mcmd(int k, char** args)
{
	//skip args[0](pass), args[1](mcmd)
	std::ifstream fileread;
	std::ofstream filewrite;			//OPTIMIZABLE_CODE
	int ncmd;
	char ch;
	bool found;
	char useful_string[1000] = { 0 };
	std::string buffer;

	fileread.open(MCMD_FILE);
	if (fileread.fail())
	{
		filewrite.open(MCMD_FILE);
		if (filewrite.fail())
			FATAL_ERROR("the file cannot be opened in the given directory");
		filewrite << 0 << '\n';
		filewrite.close();
		fileread.open(MCMD_FILE);
	}
	fileread >> ncmd;
	fileread.get();
	found = 0;
	while (!fileread.eof())
	{
		if (strcmp(useful_string, args[2]) == 0)
		{
			found = 1;
			fileread.getline(useful_string, 1000);
			buffer = useful_string;
			LOG("the command is found");
			for (int i = 0; i < 1000; i++)
			{
				buffer += fileread.get();
				if (buffer[i] == 10)
					break;
			}
			for (int i = 3; i < k; i++)
			{
				buffer = buffer + " ";
				buffer += std::string(args[i]);
				if (std::size(buffer) > 2000)
					FATAL_ERROR("there may be a fatal error hence process is being stopped");
			}
			break;
		}
		fileread.getline(useful_string, 1000);
	}
	fileread.close();
	if (!found)
	{
		SET_COLOR(COLOR_FG_Cyan, COLOR_BG_Black, 1);
		std::cout << "the required command doesn't have a macro defined for it, do you want to create new command macro?(y/n)\n";
		SET_COLOR(COLOR_FG_White, COLOR_BG_Black, 1);
		ch = std::cin.get();
		if (ch == 'y' || ch == 'Y')
		{
			filewrite.open(MCMD_FILE, std::ios::app);
			std::cin.get();
			filewrite << args[2] << '\n';
			SET_COLOR(COLOR_FG_Cyan, COLOR_BG_Black, 1);
			std::cout << "enter the command to be executed when 'mcmd " << args[2] << " <args>'  is executed - \n";
			SET_COLOR(COLOR_FG_White, COLOR_BG_Black, 1);
			int i = 0;
			do {
				if (i >= 1)
					ERROR("the given command won't execute correctly hence, rewrite it - \n");
				std::cin.getline(useful_string, 1000);
				i++;
			} while (safeCommandExec(useful_string) != 0);
			filewrite << useful_string << '\n';
			filewrite.close();
			mcmd(k, args);
		}
		return;
	}
	else
	{
		system(useful_string);
	}
}
#define SPACE(K)	for (int i = 0; i < K; i++)	std::cout.put(K);
#define COLSIZE 40
#define DRAWLINE std::cout.put(ld);\
for (int i = 0; i < colNum; i++){\
	for (int i = 0; i < COLSIZE; i++)\
		std::cout.put(l);\
	std::cout.put(ld);\
}std::cout.put('\n');

#ifndef _PRINT_TABLE
#define _PRINT_TABLE
inline void printTable(std::string* colName, std::string** cols, int colNum, int rowNum)
{
	std::cout << "\rinitialising tables..";
	int* colspaceleft = new int[colNum], * is = new int[colNum];
	int tmp = 0;
	bool contFlag = 0;
	char l = '-', ld = '+', le = '|';	//line, line divider, line end
	std::cout << '\n';
	std::cout << "\r";
	DRAWLINE;
	std::cout.put('|');
	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < COLSIZE; j++)
		{
			if (j < std::size(colName[i]))
				std::cout.put(colName[i][j]);
			else
				std::cout.put(' ');

		}
		std::cout.put('|');
	}
	std::cout.put('\n');
	DRAWLINE;

	for (int k = 0; k < rowNum; k++)
	{
		for (int i = 0; i < colNum; i++)
		{
			colspaceleft[i] = std::size(cols[k][i]);	//0,0; 0,1;	1,0; 1,1
			is[i] = colspaceleft[i];
		}
		do {
			contFlag = 0;
			for (int i = 0; i < colNum; i++)
			{
				std::cout << '|';
				for (int j = 0; j < COLSIZE; j++)
				{
					if (j < colspaceleft[i])
						std::cout.put(cols[k][i][j + (is[i] - colspaceleft[i])]);
					else
						std::cout.put(' ');
				}
				colspaceleft[i] -= COLSIZE;
				if (!contFlag)
					contFlag = colspaceleft[i] > 0;
			}
			std::cout << "| \n";
		} while (contFlag);
		DRAWLINE;
	}
	std::cout << "\ntable is printed";
	delete[] colspaceleft;
	delete[] is;
}
#endif
inline std::string floatToString(float k, int presicion)
{
	std::string r1 = "";
	unsigned int a;
	unsigned int b;
	a = int(k);
	k -= a;
	while (presicion--)
		k *= 10;
	b = k;
	while (b > 0)
	{
		r1 = char(b % 10 + 48) + r1;
		b /= 10;
	}
	r1 = "." + r1;
	while (a > 0)
	{
		r1 = char(a % 10 + 48) + r1;
		a /= 10;
	}
	return r1;
}
