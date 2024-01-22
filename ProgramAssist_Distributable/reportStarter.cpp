#include "reportStarter.h"

#define PYAUTO_HOW "\
\n>>> import pyautogui\n\
>> > screenWidth, screenHeight = pyautogui.size() # Get the size of the primary monitor.\n\
>> > currentMouseX, currentMouseY = pyautogui.position() # Get the XY position of the mouse.\n\
>> > pyautogui.moveTo(100, 150) # Move the mouse to XY coordinates.\n\
>> > pyautogui.click()          # Click the mouse.\n\
>> > pyautogui.click(100, 200)  # Move the mouse to XY coordinates and click it.\n\
>> > pyautogui.click('button.png') # Find where button.png appears on the screen and click it.\n\
>> > pyautogui.move(400, 0)      # Move the mouse 400 pixels to the right of its current position.\n\
>> > pyautogui.doubleClick()     # Double click the mouse.\n\
>> > pyautogui.moveTo(500, 500, duration = 2, tween = pyautogui.easeInOutQuad)  # Use tweening / easing function to move mouse over 2 seconds.\n\
>> > pyautogui.write('Hello world!', interval = 0.25)  # type with quarter - second pause in between each key\n\
>> > pyautogui.press('esc')     # Press the Esc key.All key names are in pyautogui.KEY_NAMES\n\
>> > with pyautogui.hold('shift') : # Press the Shift key down and hold it.\n\
pyautogui.press(['left', 'left', 'left', 'left'])  # Press the left arrow key 4 times.\n\
>> > # Shift key is released automatically.\n\
>> > pyautogui.hotkey('ctrl', 'c') # Press the Ctrl - C hotkey combination.\n\
>> > pyautogui.alert('This is the message to display.') # Make an alert box appear and pause the program until OK is clicked.\n\n\
# more about pyautogui at https://pypi.org/project/PyAutoGUI/"

reportStarter::reportStarter(std::string report_name, int stCode)
{
	reportName = report_name;
	reportPath = PROGRAMS + reportName;
	openallPath = reportPath + "\\openall.bat";
	startitPath = reportPath + "\\startit.py";
	if (stCode == WITHSTART) {
		createFile();
		fileread.open(openallPath);
		if (fileread.fail())
		{
			ERROR("the program to open files seems to not exist");
		}
		while (!fileread.eof())
		{
			fileread.getline(useful_c, 298);
			if (safeCommandExec(std::string(useful_c)) != 0)
			{
				std::cout << "the files don't open correctly, do you want to update them?(y/n)";
				ASK_UPDATE;
			}
		}
		usefulString = "python " + startitPath;
		system(usefulString.c_str());
	}
}
reportStarter::~reportStarter()
{
	std::cout << "do you want to update program open files?(y/n)";
	ASK_UPDATE;
}
void reportStarter::createFile()
{
	fileread.open(openallPath);
	if (fileread.fail())
		makeOpenFile();
	else
		fileread.close();
	fileread.open(startitPath);
	if (fileread.fail())
		makeOpenFile();
	else
		fileread.close();
}
void reportStarter::updateReport()
{
	std::cout << "do you want to update opening files manually(press 'm') or interactively(press 'i')?(m/i)";
	std::cin >> c;
	if (c == 'm')
	{
		usefulString = "notepad " + openallPath;
		system(usefulString.c_str());
		usefulString = "notepad " + startitPath;
		system(usefulString.c_str());
	}
	else
		makeOpenFile();
}
void reportStarter::makeOpenFile()
{
	filewrite.open(openallPath);
	if (filewrite.fail())
	{
		usefulString = "mkdir " + reportPath;
		system(usefulString.c_str());
		filewrite.open(openallPath);
		if (filewrite.fail())
			FATAL_ERROR("program is not able to make the necessary directories;\t possible reason - you are calling the commands while in the wrong place");
	}
	filewrite << "@echo off\n";
	filewrite << "start notepad " + reportPath + "\\tasks.txt\n";
	std::cout << "\nenter the filenames along with entire path, for the files that are to be opened, then enter '~' to finish\n";
	std::cin.get();
	while (1)
	{
		useful_c[0] = 0;
		std::cin.getline(useful_c, 100);
		if (useful_c[0] == '~')
		{
			break;
		}
		else {
			if (safeCommandExec(std::string(useful_c)) == 0)
				filewrite << "start " << useful_c << '\n';
			else {
				ERROR("The path may be invalid as it returns invalid status code. Does it work?(y/n)\n");
				std::cin >> c;
				if(c == 'y')
					filewrite << "start " << useful_c << '\n';
			}
		}
	}
	filewrite.close();
	std::cout << "\ndo you want any keyboard gestures or mouse movements to automatically be done?(y/n)\n";
	std::cin >> c;
	if (c == 'y' || c == 'Y')
	{
		filewrite.open(startitPath);
		if (filewrite.fail())
			FATAL_ERROR("the filewrite is not able to open the startit.py");
		filewrite << "'''\nturorial - \n" << PYAUTO_HOW << "\n'''";
		filewrite.close();
		usefulString = "notepad " + startitPath;
		system(usefulString.c_str());
	}
	else {
		filewrite.open(startitPath);
		filewrite.close();
	}
}
void reportStarter::log(char* text, double ct)
{
	char buf[50];
	filewrite.open(reportPath + "\\logs.txt", std::ios::app);
	time_t t = time(NULL);
	struct tm t2;
	localtime_s(&t2, &t);
	asctime_s(buf, 50, &t2);
	filewrite << "\n --- " << buf << "\t\t at " << ct << " seconds since start: " << text;
	filewrite.close();
}
void reportStarter::checklog()
{
	char a;
	usefulString = reportPath + "\\logs.txt";
	fileread.close();
	fileread.open(usefulString);
	if (fileread.fail())
	{
		LOG(reportPath + "\\logs.txt");
		ERROR("logs file is not found");
		return;
	}
	while (!fileread.eof())
	{
		fileread.get(a);
		std::cout.put(a);
	}
	fileread.close();
}