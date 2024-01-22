#include "reports.h"

/// <summary>
/// opens the given file to make sure it exists.
/// </summary>
/// <param name="fileName">:specifies name of the file</param>
/// <returns>1 on creation of new file, 0 on successfully opening the file</returns>
short int properFileOpen(std::string fileName)
{
	std::ifstream fileread;
	std::ofstream filewrite;
	fileread.open(fileName);
	if (fileread.fail())
	{
		filewrite.open(fileName);
		if (filewrite.fail())
			FATAL_ERROR("the file is not available to write into.\t possible reason - the folder requires administrator access")
		else
			filewrite.close();
		return 1;
	}
	else {
		fileread.close();
		return 0;
	}
}
void reportkeeper::displayReports()
{
	std::cout << "printing tables";
	std::string** cells;
	std::string colnames[] = { "report names", "report records", "time spent" };
	cells = new std::string * [rno];

	for (int i = 0; i < rno; i++)
		cells[i] = new std::string[COLS];

	for (int i = 0; i < rno; i++)
	{
		cells[i][0] = report_names[i];
		cells[i][1] = report_records[i];
		cells[i][2] = floatToString(workTime[i], 1);
	}
	std::cout << "\rentering the printer";
	printTable(colnames, cells, COLS, rno);

	delete[] cells;
}
inline void reportkeeper::deleteReport(char* reportName)		//TIMEKEEPER file is not deleted because the data in it depends on rno anyways.
{
	std::string rname = reportName;
	filewrite.open(REPORT_FILE);
	if (rname == "all" || rname == "*")
	{
		filewrite << 0 << '\n';
		std::cout << "deleting all records";
		filewrite.close();
	}
	else {
		filewrite << (rno - 1);
		filewrite.put('\n');
		for (int i = 0; i < rno; i++)
		{
			if (report_names[i] != rname)
			{
				filewrite << report_names[i] << '\n';
				std::cout << report_names[i] << '\n';
				filewrite << report_records[i] << '\n';
				std::cout << report_records[i] << '\n';
			}
		}
		rno--;
	}
	filewrite.close();
	delete[] report_names;
	delete[] report_records;
	initialize();
}
inline void reportkeeper::timekeeper(int startCode)
{
	std::cout << "enter name of report :";
	std::string tmp;
	int reportID = -1;
	std::cin >> tmp;
	for (int i = 0; i < rno; i++)
	{
		if (tmp == report_names[i])
		{
			reportID = i;
			break;
		}
	}
	if (reportID == -1)
	{
		ERROR("the given report doesn't exist; timer is aborted")
	}
	else {
		time_t t1, t2;
		int ch;
		float dur;
		const char* startcmd[] = {
			"log",
			"pass",
			"checklog",
			"done"
		};
		if (startCode == WITHSTART)
			std::cout << "opening work files";
		time(&t1);
		reportStarter r1(tmp, startCode);
		strcpy_s(buffer, 1000, "###starting session###");
		r1.log(buffer, 0);
		std::cout << "\nwhen you are done with work, type 'done'\n...";
		do {
			SET_COLOR(COLOR_FG_BrightMagenta, COLOR_BG_Black, 1);
			std::cout << "\n>>>";
			std::cin >> buffer;
			ch = -1;
			for (int i = 0; i < std::size(startcmd); i++)
				if (strcmp(startcmd[i], buffer) == 0)
				{
					ch = i;
					break;
				}
			switch (ch) {
			case 0:	// log
				std::cin.getline(buffer, 1000);
				LOG("entered log");
				time(&t2);
				dur = (t2 - t1);
				r1.log(buffer, dur);
				break;
			case 1:	// pass
				LOG("entered pass");
				system("start pass");
				break;
			case 2: // checklog
				LOG("entered checklog");
				SET_COLOR(COLOR_FG_BrightWhite, COLOR_BG_Black, 1)
					r1.checklog();
				break;
			case 3:	//done
				break;
			default:
				std::cout << "that is not a command in the pass report start mode. try any of the following commands - \n\tlog <something you want to keep record of>\n\tchecklog\t\t=>prints everything in log file onto screen.\n\tpass\t\t=>opens new instance of pass in interactive mode\n\tdone\t\t=>ends the session";
			}
		} while (strcmp("done", buffer) != 0);
		time(&t2);
#ifdef _DEBUG
		dur = (t2 - t1) / float(60);
#endif
#ifndef _DEBUG
		dur = (t2 - t1) / float(3600);
#endif
		std::cout << "you worked for a total time of " << dur << "hours \n";
		workTime[reportID] += dur;
		strcpy_s(buffer, 1000, "###ending work###");
		r1.log(buffer, dur);
		fileread.close();
		filewrite.open(TIMEKEEPER_FILE);
		for (int i = 0; i < rno; i++)
			filewrite << workTime[i] << '\n';
		filewrite.close();
		SET_COLOR(COLOR_FG_Green, COLOR_BG_Black, 1);
	}
}
void reportkeeper::updateReport(char* reportName, char* reportRecord)
{
	std::string rname = std::string(reportName);
	bool found = false;
	std::string rdata = std::string(reportRecord);
	filewrite.open(REPORT_FILE);
	filewrite << rno;
	filewrite.put('\n');
	for (int i = 0; i < rno; i++)
	{
		filewrite << report_names[i] << '\n';
		if (report_names[i] == rname)
		{
			filewrite << rdata << '\n';
			found = true;
		}
		else
		{
			filewrite << report_records[i] << '\n';
		}
	}
	if (!found) {
		ERROR("did not find the given report");
	}
	filewrite.close();
	delete[] report_names;
	delete[] report_records;
	initialize();
}
void reportkeeper::newReport(char* reportName, char* reportRecord)
{
	std::string rname = reportName;
	std::string rdata = reportRecord;
	std::ofstream filewrite2;
	filewrite.open(REPORT_FILE);
	filewrite2.open(TIMEKEEPER_FILE);
	filewrite << ++rno;
	filewrite.put('\n');
	for (int i = 0; i < rno - 1; i++)
	{
		filewrite << report_names[i] << '\n';
		filewrite << report_records[i] << '\n';
		filewrite2 << workTime[i] << '\n';
	}
	filewrite << rname << '\n';
	filewrite << rdata << '\n';
	filewrite2 << 0 << '\n';

	filewrite.close();
	filewrite2.close();
	delete[] report_names;
	delete[] report_records;
	delete[] workTime;
	initialize();
}
void reportkeeper::initialize()
{
	if (properFileOpen(REPORT_FILE) == 1) {
		filewrite.open(REPORT_FILE);
		filewrite << 0 << '\n';
		filewrite.close();
	}
	fileread.open(REPORT_FILE);
	fileread >> rno;		//get the first integer value that represents number of reports within file.
	report_names = new std::string[rno];
	report_records = new std::string[rno];
	workTime = new float[rno];

	fileread.get();			//get the newline character right after the report number

	for (int i = 0; i < rno; i++)
	{
		fileread.getline(buffer, 1000);	// gets report name
		report_names[i] = buffer;
		fileread.getline(buffer, 1000); // gets report data
		report_records[i] = buffer;
	}
	fileread.close();
	initTimer();
}

/// <summary>
/// initialises the workTime variable
/// if TIMEKEEPER_FILE is not available, it time for every report as 0.
/// </summary>
void reportkeeper::initTimer()
{
	if (properFileOpen(TIMEKEEPER_FILE) == 1)
	{
		filewrite.open(TIMEKEEPER_FILE);
		for (int i = 0; i < rno; i++)
			filewrite << 0 << '\n';
		filewrite.close();
	}
	fileread.open(TIMEKEEPER_FILE);
	for (int i = 0; i < rno; i++) {
		fileread >> workTime[i];
		fileread.get();
	}
	fileread.close();
}
reportkeeper::reportkeeper()
{
	buffer = new char[1000];
	initialize();
}
void showReports()
{
	reportkeeper r1;
	r1.displayReports();
}
int reporter()
{
	reportkeeper keeper1;
	std::string command;
	char rn[100], rr[100];
	int ch;
	std::string valid_commands[] = {
		"update",
		"delete",
		"create",
		"exit",
		"show",
		"start",
		"~start"
	};

	std::cout << "\nexisting commands in this mode are - ";
	std::cout << "\n\tupdate <report name> <current status>\t\t=>updates  a given report.";
	std::cout << "\n\t\tupdate ~start <report name>\t=>updates the starting command for a report.";
	std::cout << "\n\tdelete <report number>\t\t\t\t=> deletes a given report";
	std::cout << "\n\tcreate <report name>\t\t\t\t=>creates a new report with the given name and gives further prompt to enter report details";
	std::cout << "\n\texit\t\t\t\t\t\t=> exits pass report";
	std::cout << "\n\tshow\t\t\t\t\t\t=>displays report in form of a table\n";
	std::cout << "\n\tstart <report name>\t\t\t=>starts a timer for the given report and opens all the files required to start the work for that particular report";
	while (1)
	{
		ch = -1;
		std::cout << "\n>>";
		std::cin >> command;
		for (int i = 0; i < VALID_REPORT_ARGS; i++)
		{
			if (command == valid_commands[i])
			{
				ch = i;
				break;
			}
		}
		if (ch == -1)
		{
			std::cout << "that is an invalid command";
		}
		switch (ch)
		{
		case 0:	//update
			std::cout << "enter report name and report record : ";
			std::cin >> rn;
			std::cin.get();
			std::cin.getline(rr, 100);
			keeper1.updateReport(rn, rr);
			break;
		case 1:	//delete
			std::cout << "enter name of record to delete : ";
			std::cin >> rn;
			keeper1.deleteReport(rn);
			break;
		case 2:	//create
			std::cout << "enter report name and record in report to create";
			std::cin >> rn;
			std::cin.get();
			std::cin.getline(rr, 100);
			keeper1.newReport(rn, rr);
			break;
		case 3: //exit
			return 0;
			break;
		case 4: //show
			keeper1.displayReports();
			break;
		case 5:	//start
			keeper1.timekeeper(WITHSTART);
			break;
		case 6:	//~start
			keeper1.timekeeper(NOSTART);
			break;
		}

	}
}

