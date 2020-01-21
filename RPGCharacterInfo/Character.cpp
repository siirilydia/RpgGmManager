#include "Character.h"
#include"FileHandling.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

const int GAME_WIDTH = 10;
const int PLAYER_WIDTH = 10;
const int CHARNAME_WIDTH = 25;
const int HP_WIDTH = 10;
const int CURRHP_WIDTH = 10;
const int ENG_WIDTH = 10;
const int CURRENG_WIDTH = 10;
const int TOTAL_WIDTH = 100;

Character::Character()
{
	game = "not set";
	playerName = "not set";
	charName = "not set";
	hp = 0;
	currHp = 0;
	eng = 0;
	currEng = 0;
}

Character::Character(string game, string player, string charname, int hp, int chp, int eng, int ceng)
{
	this->game = game;
	this->playerName = player;
	this->charName = charname;
	this->hp = hp;
	this->currHp = chp;
	this->eng = eng;
	this->currEng = ceng;
}

//
//void Character::readFile(vector<Character>& v_char)
//{
//	ifstream fin("data.txt");
//	if (!fin)
//	{
//		cout << "Unable to open database file data.txt" << endl
//			<< "Make sure that the file exists" << endl;
//
//		exit(1);
//	}
//
//	string line;
//	int recNo = 0;
//
//	while (!fin.eof())
//	{
//		std::getline(fin, line);
//		recNo++;
//		//cout << recNo << " - " << line << endl;
//
//		istringstream iss(line);
//
//		string strGame;
//		string strPlayer;
//		string strCharName;
//		string strHp;
//		string strCurrHp;
//		string strEng;
//		string strCurrEng;
//
//		getline(iss, strGame, ',');
//		getline(iss, strPlayer, ',');
//		getline(iss, strCharName, ',');
//		getline(iss, strHp, ',');
//		getline(iss, strCurrHp, ',');
//		getline(iss, strEng, ',');
//		getline(iss, strCurrEng, ',');
//
//		Character c;
//
//		c.game = strGame;
//		c.playerName = strPlayer;
//		c.charName = strCharName;
//		c.hp = atoi(strHp.c_str());
//		c.currHp = atoi(strCurrHp.c_str());
//		c.eng = atoi(strEng.c_str());
//		c.currEng = atoi(strCurrEng.c_str());
//
//		v_char.push_back(c);
//	}
//
//	fin.close();
//}

void Character::printMenu()
{
	cout << "0. Next Turn" << endl;
	cout << "1. Add Character" << endl;
	cout << "2. Print Character Stats" << endl;
	cout << "3. Search Character" << endl;
	cout << "4. Delete Character" << endl;
	cout << "5. Save" << endl;
	cout << "6. Edit Character Stats" << endl;
	cout << "7. Exit" << endl;
}

void Character::doTask(vector <Character>& v_char, int option)
{
	cout << endl;

	string playerSearch;
	int index;

	switch (option)
	{
	case 0:
		cout << "Enter player name: ";
		cin >> playerSearch;

		nextTurn(v_char, searchCharacter(v_char, playerSearch));
		break;

	case 1:
		addCharacter(v_char);
		break;

	case 2:
		printCharacterHeader();
		for (vector<Character>::iterator it = v_char.begin(); it != v_char.end(); it++)
		{
			printCharacter(*it);
		}
		cout << setw(TOTAL_WIDTH) << setfill('-') << " " << endl;
		cout << setfill(' ');
		break;

	case 3:
		cout << "Enter player name to search: ";
		cin >> playerSearch;
		index = searchCharacter(v_char, playerSearch);
		if (index == -1)
		{
			cout << playerSearch << " does not have a character." << endl;
		}
		else
		{
			cout << playerSearch << "'s character found" << endl << endl;
			printCharacterHeader();
			printCharacter(v_char[index]);
			cout << setw(TOTAL_WIDTH) << setfill('-') << " " << endl;
			cout << setfill(' ');
		}
		break;

	case 4:
		cout << "Enter players name whose character you want to delete: ";
		cin >> playerSearch;
		if (deleteCharacter(v_char, searchCharacter(v_char, playerSearch)))
		{
			cout << playerSearch << "'s character deleted succesfully" << endl;
		}
		else
		{
			cout << playerSearch << "'s character could not be deleted" << endl;
		}
		break;

	case 5:
		FileHandling fh;
		fh.saveToFile(v_char);
		break;

	case 6:
		cout << "Enter player name: ";
		cin >> playerSearch;
		//index = searchCharacter(v_char, playerSearch);
		editCharacter(v_char, searchCharacter(v_char, playerSearch));

		break;

	default:
		cout << "Invalid menu option chosen, valid options are form 1 to 6." << endl;
		break;
	}
}

void Character::addCharacter(vector <Character>& v_char)
{
	Character temp;
	cout << "Game: " << endl;
	cin >> temp.game;

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	bool isDuplicate = false;

	do
	{
		cout << "Player name: " << endl;
		cin >> temp.playerName;

		isDuplicate = false;
		if (searchCharacter(v_char, temp.playerName) != -1)
		{
			isDuplicate = true;
			cout << temp.playerName
				<< " already has a character, please input unique name" << endl;
		}
	} while (isDuplicate);

	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "Character Name: " << endl;
	std::getline(cin, temp.charName);

	cout << "Max Hp: " << endl;
	cin >> temp.hp;

	cout << "Current Hp: " << endl;
	cin >> temp.currHp;

	cout << "Max Energy: " << endl;
	cin >> temp.eng;

	cout << "Current Energy: " << endl;
	cin >> temp.currEng;

	v_char.push_back(temp);
	cout << endl << "Character for " << temp.playerName << " added succesfully" << endl;
	cout << endl << "Total players: " << v_char.size() << endl;
}

int Character::searchCharacter(vector <Character> v_char, string targetPlayer)
{
	for (int i = 0; i < v_char.size(); i++)
	{
		if (v_char[i].playerName == targetPlayer)
		{
			return i;
		}
	}
	return -1;
}

void Character::printCharacterHeader()
{
	cout << endl;

	cout << setw(GAME_WIDTH) << left << "Game"
		<< setw(PLAYER_WIDTH) << left << "Player"
		<< setw(CHARNAME_WIDTH) << left << "Character"
		<< setw(HP_WIDTH) << right << "Max Hp"
		<< setw(CURRHP_WIDTH) << right << "Hp"
		<< setw(ENG_WIDTH) << right << "Max Eng"
		<< setw(CURRENG_WIDTH) << right << "Eng"
		<< endl;

	cout << setw(TOTAL_WIDTH) << setfill('-') << " " << endl;
	cout << setfill(' ');
	//for (vector<Character>::iterator it = v_char.begin(); it != v_char.end(); it++)
	//{
	//	printCharacter(*it);
	//}

	//cout << setw(TOTAL_WIDTH) << setfill('-') << " " << endl;
	//cout << setfill(' ');
}

void Character::printCharacter(Character c)
{
	cout << setw(GAME_WIDTH) << left << c.game
		<< setw(PLAYER_WIDTH) << left << c.playerName
		<< setw(CHARNAME_WIDTH) << left << c.charName
		<< setw(HP_WIDTH) << right << c.hp
		<< setw(CURRHP_WIDTH) << right << c.currHp
		<< setw(ENG_WIDTH) << right << c.eng
		<< setw(CURRENG_WIDTH) << right << c.currEng
		<< endl;
}

bool Character::deleteCharacter(vector <Character>& v_char, int targetCharId)
{
	if (targetCharId == -1)
	{
		return false;
	}

	else
	{
		cout << "Character to delete found: " << endl;
		cout << endl;
		printCharacterHeader();
		printCharacter(v_char[targetCharId]);
		cout << endl;
		cout << "Are you sure to delete? Input 1 to delete, 0 to exit" << endl;

		int option;
		cin >> option;

		if (option == 1)
		{
			v_char.erase(v_char.begin() + targetCharId);
			return true;
		}

		return false;
	}
}

void Character::editCharacter(vector <Character>& v_char, int index)
{
	if (index == -1)
	{
		cout << "Character not found" << endl;
		return;
	}

	printCharacterHeader();
	printCharacter(v_char[index]);

	cout << endl << "Input new character info, input 0 to keep it as same" << endl;

	string charName;
	cout << "Characters name: ";
	cin >> charName;
	if (charName != "0")
	{
		v_char[index].charName = charName;
	}
	int newStat;
	cout << "Max hp: ";
	cin >> newStat;
	if (newStat != 0)
	{
		v_char[index].hp = newStat;
	}
	cout << "Current hp: ";
	cin >> newStat;
	if (newStat != 0)
	{
		v_char[index].currHp = newStat;
	}
	cout << "Max energy: ";
	cin >> newStat;
	if (newStat != 0)
	{
		v_char[index].eng = newStat;
	}
	cout << "Current energy: ";
	cin >> newStat;
	if (newStat != 0)
	{
		v_char[index].currEng = newStat;
	}

	cout << endl << "Updated stats: " << endl << endl;

	printCharacterHeader();
	printCharacter(v_char[index]);
}

void Character::nextTurn(vector <Character>& v_char, int index)
{
	if (index == -1)
	{
		cout << "Player not found" << endl;
		return;
	}

	printCharacterHeader();
	printCharacter(v_char[index]);
	cout << string(2, '\n');
	printTurnOptions();

	int action = 0;

	while (action != 5)
	{
		cout << endl << "Input action to do: ";
		cin >> action;

		int effect = 0;

		switch (action)
		{
		case 1:
			cout << "Input how much energy to use:" << endl;
			cin >> effect;
			v_char[index].currEng -= effect;
			cout << effect << " energy used. Current energy: " << v_char[index].currEng << endl;
			break;

		case 2:
			cout << "Input how much energy to add:" << endl;
			cin >> effect;
			v_char[index].currEng += effect;
			cout << effect << " energy added. Current energy: " << v_char[index].currEng << endl;
			break;

		case 3:
			cout << "Input how much damage to take:" << endl;
			cin >> effect;
			v_char[index].currHp -= effect;
			cout << effect << " damage taken. Current hp: " << v_char[index].currHp << endl;
			break;

		case 4:
			cout << "Input healing amount: " << endl;
			cin >> effect;
			v_char[index].currHp += effect;
			cout << "Healed " << effect << " points. Current hp: " << v_char[index].currHp << endl;

			break;

		case 5:
			cout << "Ending turn" << endl;
			break;

		default:
			cout << "Invalid input" << endl;
			break;
		}
	}
}

void Character::printTurnOptions()
{
	cout << "1. Use Energy" << endl;
	cout << "2. Add Energy" << endl;
	cout << "3. Take Damage" << endl;
	cout << "4. Heal" << endl;
	cout << "5. End Turn" << endl;
}

string Character::ToString(Character c)
{
	ostringstream oss;
	oss << game << "," << playerName << "," << charName << ","
		<< hp << "," << currHp << "," << eng << "," << currEng;
	return oss.str();
}
//
//void Character::saveToFile(vector <Character> v_char)
//{
//	ofstream fout("data.txt");
//	if (!fout)
//	{
//		cout << "Unable to open the file data.txt" << endl;
//		return;
//	}
//
//	int recCount = 0;
//	for (vector<Character>::iterator it = v_char.begin(); it != v_char.end(); ++it)
//	{
//		fout << it->game << "," << it->playerName << "," << it->charName << ","
//			<< it->hp << "," << it->currHp << "," << it->eng << "," << it->currEng;
//
//		recCount++;
//
//		if (recCount != v_char.size())
//		{
//			fout << endl;
//		}
//	}
//
//	fout.close();
//
//	cout << "Save succesful, total of " << recCount << " characters data saved" << endl;
//}
