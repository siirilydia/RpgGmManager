#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Character.h"

class FileHandling
{
private:
public:
	void readFile(vector<Character>& v_char);
	void saveToFile(vector <Character> v_char);
};

#endif

