#include "FileHandling.h"
#include "Character.h"

void FileHandling::readFile(vector<Character>& v_char)
{
	ifstream fin("data.txt");
	if (!fin)
	{
		cout << "Unable to open database file data.txt" << endl
			<< "Make sure that the file exists" << endl;

		exit(1);
	}

	string line;
	int recNo = 0;

	while (!fin.eof())
	{
		std::getline(fin, line);
		recNo++;
		//cout << recNo << " - " << line << endl;

		istringstream iss(line);

		string strGame;
		string strPlayer;
		string strCharName;
		string strHp;
		string strCurrHp;
		string strEng;
		string strCurrEng;

		getline(iss, strGame, ',');
		getline(iss, strPlayer, ',');
		getline(iss, strCharName, ',');
		getline(iss, strHp, ',');
		getline(iss, strCurrHp, ',');
		getline(iss, strEng, ',');
		getline(iss, strCurrEng, ',');

		Character c(strGame,strPlayer,strCharName,atoi(strHp.c_str()),atoi(strCurrHp.c_str()),atoi(strEng.c_str()),atoi(strCurrEng.c_str()));

		/*c.game = strGame;
		c.playerName = strPlayer;
		c.charName = strCharName;
		c.hp = atoi(strHp.c_str());
		c.currHp = atoi(strCurrHp.c_str());
		c.eng = atoi(strEng.c_str());
		c.currEng = atoi(strCurrEng.c_str());*/

		v_char.push_back(c);
	}

	fin.close();
}

void FileHandling::saveToFile(vector <Character> v_char)
{
	ofstream fout("data.txt");
	if (!fout)
	{
		cout << "Unable to open the file data.txt" << endl;
		return;
	}

	int recCount = 0;
	for (vector<Character>::iterator it = v_char.begin(); it != v_char.end(); ++it)
	{
		//fout << it->game << "," << it->playerName << "," << it->charName << ","
		//	<< it->hp << "," << it->currHp << "," << it->eng << "," << it->currEng;
		fout << it->ToString(*it);
		recCount++;

		if (recCount != v_char.size())
		{
			fout << endl;
		}
	}

	fout.close();

	cout << "Save succesful, total of " << recCount << " characters data saved" << endl;
}
