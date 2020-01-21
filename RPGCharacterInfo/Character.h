#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

class Character
{
private:
	string game;
	string playerName;
	string charName;
	int hp;
	int currHp;
	int eng;
	int currEng;
public:
	Character();
	Character(string game, string player, string charname, int hp, int chp, int eng, int ceng);
	void printMenu();
	void doTask(vector <Character>& v_char, int option);
	void addCharacter(vector <Character>& v_char);
	int searchCharacter(vector <Character> v_char, string targetPlayer);
	void printCharacterHeader();
	void printCharacter(Character c);
	bool deleteCharacter(vector <Character>& v_char, int targetCharId);
	void editCharacter(vector <Character>& v_char, int index);
	void nextTurn(vector <Character>& v_char, int index);
	void printTurnOptions();
	string ToString(Character c);
};
#endif
