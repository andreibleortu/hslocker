#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <cstring>
using namespace std;

ifstream fin("11F.txt");
ofstream fout("11F.tmp");
int n, nameLenMax;
int opt;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct stdt
{
	char nume[80];
	int hasKey;
	int lockerNo, pair;
} hsClass[40];

void cls()
{
	system("CLS");
}
void fillStd(char line[80], int crt)
{
	int i = 0;
	while (line[i] != ';')
	{
		hsClass[crt].nume[i] = line[i];
		i++;
	}
	hsClass[crt].nume[i + 1] = '\0';
	int crtNameLen = strlen(hsClass[crt].nume);
	if (nameLenMax < crtNameLen)
	{
		nameLenMax = crtNameLen;
	}
	i++;
	hsClass[crt].hasKey = line[i] - '0';
	i++;
	hsClass[crt].lockerNo = atoi(strtok(line + i, ";"));
	i = i + 3;
	if (hsClass[crt].lockerNo > 9 && hsClass[crt].lockerNo < 100)
	{
		i++;
	}
	if (hsClass[crt].lockerNo > 99)
	{
		i++;
	}
	hsClass[crt].pair = atoi(strtok(line + i, "\n"));
}

void importDB(int i)
{
	if (i <= n)
	{
		char linie[100];
		fin.getline(linie, 100);
		fillStd(linie, i);
		importDB(i + 1);
	}
}

void outputDB(int i)
{
	if (i == 1)
	{
		cout << right << setw(strlen("Index")) << "Index " << left << setw(nameLenMax) << "Nume " << right << setw(strlen("Are cheie")) << "Are cheie " << setw(strlen("Nr. dulap")) << "Nr. dulap " << setw(strlen("Pereche")) << "Pereche" << '\n'
			 << flush;
	}
	if (i <= n)
	{
		if (hsClass[i].hasKey == 1)
		{
			SetConsoleTextAttribute(hConsole, 10);
		}
		else if (hsClass[i].hasKey == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << right << setw(strlen("Index")) << i << " " << flush;
		cout << left << setw(nameLenMax) << hsClass[i].nume << flush;
		if (hsClass[i].hasKey == 2)
		{
			cout << right << setw(strlen("Key")) << "none" << flush;
		}
		else
		{
			cout << right << setw(strlen("Key")) << hsClass[i].hasKey << flush;
		}
		if (!hsClass[i].lockerNo)
		{
			cout << right << setw(strlen("Locker no.")) << '-' << flush;
		}
		else
		{
			cout << right << setw(strlen("Locker no.")) << hsClass[i].lockerNo << flush;
		}

		if (!hsClass[i].pair)
		{
			cout << right << setw(strlen("Pair")) << "-" << '\n'
				 << flush;
		}
		else
		{
			cout << right << setw(strlen("Pair")) << hsClass[i].pair << '\n'
				 << flush;
		}
		outputDB(i + 1);
	}
	if (i == n)
	{
		SetConsoleTextAttribute(hConsole, 15);
	}
}

void writeToFile(int i)
{
	if (i == 1)
	{
		fout << n << '\n';
	}
	if (i == n)
	{
		fout << hsClass[i].nume << ';' << hsClass[i].hasKey << ';' << hsClass[i].lockerNo << ';' << hsClass[i].pair << '\n';
		fin.close();
		fout.close();
		system("del 11F.txt");
		system("copy 11F.tmp 11F.txt");
	}
	if (i <= n)
	{
		fout << hsClass[i].nume << ';' << hsClass[i].hasKey << ';' << hsClass[i].lockerNo << ';' << hsClass[i].pair << '\n';
		writeToFile(i + 1);
	}
}
void syncPair(int orig, int dest)
{
	hsClass[dest].hasKey = hsClass[orig].hasKey;
	hsClass[dest].lockerNo = hsClass[orig].lockerNo;
	hsClass[dest].pair = orig;
}
void addKey()
{
	int indexModif, dulapModif, perecheModif;
	cout << endl
		 << "Input student no." << endl
		 << flush;
	cin >> indexModif;
	hsClass[indexModif].hasKey = 1;
	cout << endl
		 << "Which locker no.?" << endl
		 << flush;
	cin >> dulapModif;
	hsClass[indexModif].lockerNo = dulapModif;
	cout << endl
		 << "Has a key (y/n)" << endl
		 << flush;
	char arePereche;
	cin >> arePereche;
	if (arePereche == 'y')
	{
		cout << "Enter student's pair" << endl
			 << flush;
		cin >> perecheModif;
		hsClass[indexModif].pair = perecheModif;
		syncPair(indexModif, perecheModif);
	}
}
void removeKey()
{
	int indexModif;
	cout << endl
		 << "Input student no." << endl
		 << flush;
	cin >> indexModif;
	hsClass[indexModif].hasKey = 0;
	hsClass[indexModif].lockerNo = 0;
	if (hsClass[indexModif].pair != 0)
	{
		syncPair(indexModif, hsClass[indexModif].pair);
		hsClass[hsClass[indexModif].pair].pair = 0;
		hsClass[indexModif].pair = 0;
	}
}

void zeroAll(int i)
{
	if (i <= n)
	{
		hsClass[i].hasKey = 0;
		hsClass[i].lockerNo = 0;
		hsClass[i].pair = 0;
		zeroAll(i + 1);
	}
}
void markNone()
{
	cout << "Input student no." << endl
		 << flush;
	int stdt;
	cin >> stdt;
	hsClass[stdt].hasKey = 2;
}

void showNoKey(int i)
{
	if (i == 1)
	{
		cls();
		cout << right << setw(strlen("Index")) << "Index " << left << setw(nameLenMax) << "Name " << right << setw(strlen("Key")) << "Key " << setw(strlen("Locker no.")) << "Locker no. " << setw(strlen("Pair")) << "Pair" << '\n'
			 << flush;
	}
	if (i <= n)
	{
		if (hsClass[i].hasKey == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << right << setw(strlen("Index")) << i << " " << flush;
			cout << left << setw(nameLenMax) << hsClass[i].nume << flush;
			cout << right << setw(strlen("Key")) << hsClass[i].hasKey << flush;
			cout << right << setw(strlen("Locker no.")) << '-' << flush;
			cout << right << setw(strlen("Pair")) << "-" << '\n'
				 << flush;
		}
		showNoKey(i + 1);
	}
	if (i == n)
	{
		SetConsoleTextAttribute(hConsole, 15);
		system("pause");
	}
}
void announceOptions()
{
	cout << endl
		 << "1. Add key" << endl
		 << "2. Remove key" << endl
		 << "3. Never received key" << endl
		 << "4. Show students with no key" << endl
		 << "5. Write and exit" << endl
		 << flush;
}

int main()
{
	cls();
	fin >> n;
	fin.get();
	importDB(1);
	outputDB(1);
	while (opt != 5)
	{
		announceOptions();
		cin >> opt;
		if (opt == 1)
		{
			addKey();
		}
		else if (opt == 2)
		{
			removeKey();
		}
		else if (opt == 3)
		{
			markNone();
		}
		else if (opt == 4)
		{
			showNoKey(1);
		}
		else if (opt == 6)
		{
			zeroAll(1);
		}
		cls();
		outputDB(1);
	}
	writeToFile(1);
	system("pause");
}
