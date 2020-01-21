// RPGCharacterInfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Character.h"
#include "FileHandling.h"

using namespace std;

int main()
{
	Character c1;
	FileHandling fh;
	vector <Character> v_char;

	fh.readFile(v_char);
	cout << "Total " << v_char.size() << " characters read from the data file." << endl << endl;

	bool quit = false;
	int option;

	while (!quit)
	{
		c1.printMenu();
		cout << endl << "Input your option: ";
		cin >> option;
		if (option == 7)
		{
			cout << "Do you wish to save before exiting? Input 1 to save, 0 to exit" << endl;
			cin >> option;
			if (option == 1)
			{
				FileHandling fh;
				fh.saveToFile(v_char);
				cout << "Exiting program" << endl;
			}
			else
			{
				cout << "Exiting program without saving" << endl;
			}
			quit = true;
		}
		else
		{
			c1.doTask(v_char, option);
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		// decided to use this to "tidy up" the console a bit instead of system commands
		// since i read so many warnings about clearing the console with that
		cout << string(2, '\n');
	}

	return 0;
}