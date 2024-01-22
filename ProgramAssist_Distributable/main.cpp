		/****************************************************************************************************
		*																									*
		* PASS - Program Assistant Distributable Version													*
		*																									*
		* Developed by Ryuou 02																				*
		*																									*
		* This is a simple terminal program made purely for functionality and not much for ease of use but	*
		* in the end it aims to make the use of a computer more efficiently.								*
		*																									*
		* It is currently developed on windows OS, will be released for Linux in future						*
		*																									*
		* place the compiled file in the c:\windows\system32\ folder to easily use the pass command			*
		*																									*
		*																									*
		*****************************************************************************************************/
#include<string.h>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include "includes.h"
#include "reports.h"
#include"colorCodes.h"

#define VERSION 12

#define ARGS std::size(commands)				//total number of existing arguments
#define DEFAULT_DEBUG_ARG "exit"



// the nothing commands are useless
const char* commands[]{
	"/?",			//1. help
	"help",			//2. help
	"open",			//3. open programs
	"try",			//4. open notepad to try random things
	"search",		//5. search things on internet, uses duckduckgo search engine by default
	"message",		//6. message people directly with ip address ---------------------------------------	not implemented
	"backup",		//7. create backup of all the files in a given directory in another directory ------	not implemented
	"report",		//8. give report of ongoing projects
	"cmd",			//9. execute command prompt commands
	"show",			//10. show all programs that can be opened
	"nothing",		//11. does nothing
	"update",		//12. checks for update and updates program.
	"f_request",	//13. user can request for features using this command.-----------------------------	not implemented
	"bye",			//14. say bye and exit
	"exit",			//15. to exit
	"calc",			//16. to calculate any expression --------------------------------------------------	not implemented
	"mcmd",			//17. to get macro commands, like suppose you needed to type some huge line just to get some command executed, like checking battery level, you can store it as a command macro.
	"sleep"			//18. shutdown the computer
};

std::ifstream fileread;
std::ofstream filewrite;
char* shit;
std::string browser1;
std::string useful_string;
int ch = -1;
char a;

void pass(int k, char** args)
{
	std::string buffer2;
	char* buffer;
	int urlLen = 0;
	int tmp_int = 0;
	ch = -1;
	for (int i = 0; i < ARGS; i++)
	{
		if (strcmp(args[1], commands[i]) == 0)
		{
			ch = i;
		}
	}
	LOG("choosing option number " << ch);
	switch (ch)
	{
	case 2:	//open programs
		if (k < 2) {
			std::cout << "usage of this argument =>\npass open <program name>";
			return;
		}
		useful_string = args[2];
		if (useful_string != "update")
			openProgram(args[2]);
		else {
			if (k < 4)
			{
				std::cout << "usage of this argument =>\n\tpass open update <program name>";
				return;
			}
			shit = new char[1000];
			std::cout << "enter directory of program - ";
			std::cin.getline(shit, 1000);
			updatePrograms(args[3], shit);
			delete[] shit;
		}
		break;

	case 3:	//try
		system("notepad .\\PASS_files\\try_stuff.txt");
		break;

	case 4:	//search

		//convert string to url encoded

		/*********************************************
		* pass search
		* 
		* search ~g <query> searches the query on google using browser 1, as defined in the SETTINGS file
		* 
		* search ~secure <webpage url> gets the page source of the given url and opens it on your computer after disconnecting wifi to prevent data being sent to server.
		* --uses curl browser
		* 
		* search ~youtube <query> searches the query on youtube using browser 1
		* 
		* search ~yt <query> does the same thing as above command
		* 
		*********************************************/
		if (strcmp(args[2], "~g") == 0) {
			buffer2 = "start " + browser1 + " https://www.google.com/search?q=";
			tmp_int = 3;
		}
		else if (strcmp(args[2], "~secure") == 0)
		{
			buffer2 = "curl ";
			buffer2 += std::string(args[3]);
			buffer2 += " > webpage.html";
			system(buffer2.c_str());
			system("netsh wlan disconnect");
			useful_string = browser1 + ".\\webpage.html";
			system(useful_string.c_str());
			break;
		}
		else if (strcmp(args[2], "~youtube") == 0 || strcmp(args[2], "~yt") == 0) {
			buffer2 = "start " + browser1 + " https://www.youtube.com/results?search_query=";
			for (int i = 0; i < k - 3; i++)
			{
				buffer2 += std::string(args[i + 3]);
				buffer2 += "+";
			}
			system(buffer2.c_str());
			LOG(buffer2);
			break;
		}
		else {
			buffer2 = "start " + browser1 + " https://duckduckgo.com/?q=";
			tmp_int = 2;
		}

		urlLen = std::size(buffer2);

		for (int i = 0; i < k - tmp_int; i++)
		{
			LOG(strlen(args[i + tmp_int]));
			for (int j = 0; j < strlen(args[i + tmp_int]); j++)
			{
				switch (args[i + tmp_int][j]) {
				case '+':
					buffer2 += "%2B";
					break;
				case '/':
					buffer2 += "%2F";
					break;
				case '(':
					buffer2 += "%28";
					break;
				case ')':
					buffer2 += "%29";
					break;
				case '=':
					buffer2 += "%3D";
					break;
				case '`':
					buffer2 += "%60";
					break;
				case '!':
					buffer2 += "%21";
					break;
				case '&':
					buffer2 += "%26";
					break;
				default:
					buffer2 += args[i + tmp_int][j];
				}
			}
			buffer2 += "+";
		}
		system(buffer2.c_str());
		break;

	case 5:	//	message
		break;

	case 6:	//	backup
		break;

	case 7:	//report
		/************************************************************************
		* pass report
		* -- this is a very useful command, perhaps the only useful command here
		* 
		* usage is defined in the help file
		* 
		*************************************************************************/
		SET_COLOR(COLOR_FG_Green, COLOR_BG_Black, 1);
		if (k < 3) {
			reporter();		//opens reports in interactive mode.
		}
		else
		{
			ch = -1;
			useful_string = args[2];
			const char* report_commands[] = {
				"update",
				"delete",
				"create",
				"exit",
				"show",
				"start",
				"~start"
			};
			for (int i = 0; i < std::size(report_commands); i++)
			{
				if (strcmp(args[2], report_commands[i]) == 0)
				{
					ch = i;
					break;
				}
			}

			reportkeeper r1;
			char rn[100], rr[100];
			switch (ch)
			{
			case 0:	//update
				if (k < 4)
				{
					ERROR("usage of this argument => pass report update <report name>");
					break;
				}
				std::cout << "enter report record";
				std::cin.get();
				std::cin.getline(rr, 100);
				r1.updateReport(args[3], rr);
				break;
			case 1:	//delete
				if (k < 4) {
					std::cout << "enter name of record to delete : ";
					std::cin >> rn;
					r1.deleteReport(rn);
				}
				else {
					r1.deleteReport(args[3]);
				}
				break;
			case 2:	//create
				if (k < 4)
				{
					ERROR("usage of this argument => pass report create <report name>");
					break;
				}
				if (k < 5) {
					std::cout << "enter report record to create : ";
					std::cin.get();
					std::cin.getline(rr, 100);
					r1.newReport(args[3], rr);
					break;
				}
				r1.newReport(args[3], args[4]);
				break;
			case 3: //exit
				return;
				break;
			case 4: //show
				r1.displayReports();
				break;
			case 5: //start
				r1.timekeeper(WITHSTART);
				break;
			case 6:	//~start
				r1.timekeeper(NOSTART);
				break;
			default:
				fileread.open(REPORT_HELP_FILE);
				std::cout << "\nHow to use pass report - ";
				char a;
				while (!fileread.eof())
				{
					a = fileread.get();
					std::cout << a;
				}
				fileread.close();
				break;
			}
		}
		RESET_COLOR
		break;

	case 8:	//cmd		==> opens command prompt and executes the command
		SET_COLOR(COLOR_FG_BrightRed, COLOR_BG_BrightBlack, 0);
		if (k < 3)
		{
			ERROR("not enough args");
			break;
		}
		buffer = new char[1000];
		buffer[0] = 0;
		for (int i = 0; i < k - 2; i++)
		{
			strcat_s(buffer, 1000, args[i + 2]);
			strcat_s(buffer, 1000, " ");
		}
		system(buffer);
		if(safeCommandExec(buffer) != 0)
		{
			ERROR("it seems that the command may have not executed correctly");
		}

		delete[] buffer;
		RESET_COLOR;
		break;

	case 9:	//show	
		fileread.open(PROGRAM_FILE);
		buffer = new char[1000];
		fileread >> tmp_int;
		fileread.get();
		for (int i = 0; i < tmp_int; i++)
		{
			fileread.getline(buffer, 1000);
			std::cout << "\nprogram name: \t" << buffer << '\n';
			fileread.getline(buffer, 1000);
			std::cout << "program path: \t" << buffer << '\n';
		}
		fileread.close();
		delete[] buffer;
		break;

	case 11:		//update
		if (k > 2) {
			RESET_COLOR
			exit(VERSION);
		}
		else {
			std::cout << "\nrun the command pass-update to get update\n";
		}
		break;
	case 12:		//f_request
		break;

	case 13:		//bye
		std::cout << "bye bye";
		RESET_COLOR;
		exit(0);
		break;

	case 14:		//exit
		std::cout << "bye bye";
		RESET_COLOR;
		exit(0);
	case 15:		//calc
		break;
	case 16:		//mcmd
		mcmd(k, args);
		break;
	case 17:		//sleep
		system("shutdown /p");
		break;

	default:
		SET_COLOR(COLOR_FG_Green, COLOR_BG_Black, 1);
		if (args[k - 1][strlen(args[k - 1]) - 1] == '?')	// argument passed ends with a question mark means that it is a question
		{
			const char* question_type[] = { "why", "what", "how" };
			srand(time(NULL));
			int c = -1;
			for (int i = 0; i < std::size(question_type); i++)
			{
				if (std::string(args[0]) == std::string(question_type[i]))
				{
					c = i;
				}
			}
			switch (c) {
			case 0:
			case 1:
			case 2:
			default:
				rand() % 2 == 0 ? printf("yes") : printf("no");
			}
			RESET_COLOR;
			return;
		}
		else if (args[k - 1][strlen(args[k - 1]) - 1] == '!')	// argument passed ends with a question mark means that it is a question
		{
			printf("YEAAAH!!!");
			RESET_COLOR;
			return;
		}
		if (k <= 1)
			FATAL_ERROR("why so less arguments!!");
		if (strcmp(args[1], "help") != 0)
		{
			std::cout << "the argument - ";
			for (int i = 0; i < k; i++)
			{
				std::cout << args[i] << " ";
			}
			std::cout << " is invalid";
		}
		fileread.open(README);
		if (fileread.fail()){
			std::cout << "### ERROR: couldn't open readme file. ###";
			return;
		}
		std::cout << "\nusage of program - ";
		do{	
			a = fileread.get();
			std::cout.put(a);
		} while (!fileread.eof());
		fileread.close();
		break;

	}

}

void setSettings()
{
	filewrite.open(SETTINGS);
	SET_COLOR(COLOR_FG_Cyan, COLOR_BG_Black, 22);
	std::cout << "enter default browser name (chrome, msedge, firefox, brave, ...(you should be able to open the browser using run with this name))\n>>";
	RESET_COLOR;
	std::cin >> browser1;
	filewrite << "default browser - " << '\n' << browser1;
	SET_COLOR(COLOR_FG_Cyan, COLOR_BG_Black, 22);
	std::cout << "you can change the settings in PASS_files/settings\n";
	RESET_COLOR;
	filewrite.close(); 
}

void loadSettings()
{
	fileread.open(SETTINGS);
	while (fileread.get() != '\n')
		if (fileread.eof())
		{
			ERROR("the settings file seems to be written incorrectly, hence rewriting the settings...\n");
			setSettings();
		}
	fileread >> browser1;
	LOG("browser selected => " << browser1);
	fileread.close();
}

int main(int k, char** args)
{
	system("title PASS");

	fileread.open(SETTINGS);
	if (fileread.fail())
	{
		//set variables based on settings
		setSettings();
	}
	else {
		//set variable values
		fileread.close();
		loadSettings();
	}
	LOG(std::size(commands));
	filewrite.open("\\PASS_files\\metadata");
	if (filewrite.fail())
	{
		system("mkdir \\PASS_files");
		filewrite.open("\\PASS_files\\metadata");
		if (filewrite.fail())
		{
			std::cout << "\nERROR : not able to open program files!";
			std::cout << "\n possible fix - open pass with administrative power and it can finally take over your system";
			std::cin.get();
			return 0;
		}
		else {
			filewrite.close();
		}
	}
	filewrite.close();
	if (k > 1) {
		pass(k, args);
	}
	else {
		char** iargs;
		int count;
		char buffer2[1000] = { 0 };
		SET_COLOR(COLOR_FG_Green, COLOR_BG_Black, 4)
			std::cout << "#####\tPROGRAM ASSISTANT VERSION " << VERSION / (float)10 << " \t######";

		while (1) {
			RESET_COLOR
				std::cout << "\n>> ";
			for (int i = 0; i < 1000; i++)
				buffer2[i] = 0;
			std::cin.getline(buffer2, 1000);
			count = 1;
			if (strlen(buffer2) == 0)
				continue;
			for (int i = 0; buffer2[i] != 10 && buffer2[i] != 0; i++)
			{
				if (buffer2[i] == 32)
					count++;
			}
			LOG("count = " << count);
			iargs = new char* [count + 1];
			int j;

			iargs[0] = new char[10];
			iargs[0][0] = 0;

			for (int i = 1, c = 0; i < count + 1; i++, c++)
			{
				if (i == count + 1)
					FATAL_ERROR("too much arguments even though so less");
				
				iargs[i] = new char[500];
				for (j = 0; buffer2[c] != 32 && buffer2[c] != 0; j++, c++)
				{
					if (c > 998 || j > 498)
						FATAL_ERROR("the fuck is going on?");

					iargs[i][j] = buffer2[c];
				}
				iargs[i][j] = 0;
			}
			SET_COLOR(COLOR_FG_Cyan, COLOR_BG_Black, 22);
			pass(count + 1, iargs);
			for (int i = 0; i < count + 1; i++)
				delete[] iargs[i];
			delete[] iargs;
		}
	}
}