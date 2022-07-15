#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <cstring>
using namespace std;

ifstream fin("11F.txt");
ofstream fout("11F.tmp");
int n, nameLenMax;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct elev
{
	char nume[80];
	int areCheie;
	int nrDulap, pereche;
} c11F[40];

void cls()
{
	system("CLS");
}
void fillElev(char line[80], int crt)
{
	int i = 0;
	while (line[i] != ';')
	{
		c11F[crt].nume[i] = line[i];
		i++;
	}
	c11F[crt].nume[i + 1] = '\0';
	int crtNameLen = strlen(c11F[crt].nume);
	if (nameLenMax < crtNameLen)
	{
		nameLenMax = crtNameLen;
	}
	i++;
	c11F[crt].areCheie = line[i] - '0';
	i++;
	c11F[crt].nrDulap = atoi(strtok(line + i, ";"));
	i = i + 3;
	if (c11F[crt].nrDulap > 9 && c11F[crt].nrDulap < 100)
	{
		i++;
	}
	if (c11F[crt].nrDulap > 99)
	{
		i++;
	}
	c11F[crt].pereche = atoi(strtok(line + i, "\n"));
}

void importDB(int i)
{
	if (i <= n)
	{
		char linie[100];
		fin.getline(linie, 100);
		fillElev(linie, i);
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
		if (c11F[i].areCheie == 1)
		{
			SetConsoleTextAttribute(hConsole, 10);
		}
		else if (c11F[i].areCheie == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << right << setw(strlen("Index")) << i << " " << flush;
		cout << left << setw(nameLenMax) << c11F[i].nume << flush;
		if (c11F[i].areCheie == 2)
		{
			cout << right << setw(strlen("Are cheie")) << "none" << flush;
		}
		else
		{
			cout << right << setw(strlen("Are cheie")) << c11F[i].areCheie << flush;
		}
		if (!c11F[i].nrDulap)
		{
			cout << right << setw(strlen("Nr. dulap")) << '-' << flush;
		}
		else
		{
			cout << right << setw(strlen("Nr. dulap")) << c11F[i].nrDulap << flush;
		}

		if (!c11F[i].pereche)
		{
			cout << right << setw(strlen("Pereche")) << "-" << '\n'
				 << flush;
		}
		else
		{
			cout << right << setw(strlen("Pereche")) << c11F[i].pereche << '\n'
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
		fout << c11F[i].nume << ';' << c11F[i].areCheie << ';' << c11F[i].nrDulap << ';' << c11F[i].pereche << '\n';
		fin.close();
		fout.close();
		system("del 11F.txt");
		system("copy 11F.tmp 11F.txt");
	}
	if (i <= n)
	{
		fout << c11F[i].nume << ';' << c11F[i].areCheie << ';' << c11F[i].nrDulap << ';' << c11F[i].pereche << '\n';
		writeToFile(i + 1);
	}
}
void syncPereche(int orig, int dest)
{
	c11F[dest].areCheie = c11F[orig].areCheie;
	c11F[dest].nrDulap = c11F[orig].nrDulap;
	c11F[dest].pereche = orig;
}
void addCheie()
{
	int indexModif, dulapModif, perecheModif;
	cout << endl
		 << "Introdu indexul elevului" << endl
		 << flush;
	cin >> indexModif;
	c11F[indexModif].areCheie = 1;
	cout << endl
		 << "Ce numar dulap?" << endl
		 << flush;
	cin >> dulapModif;
	c11F[indexModif].nrDulap = dulapModif;
	cout << endl
		 << "Are pereche? (y/n)" << endl
		 << flush;
	char arePereche;
	cin >> arePereche;
	if (arePereche == 'y')
	{
		cout << "Introdu perechea elevului" << endl
			 << flush;
		cin >> perecheModif;
		c11F[indexModif].pereche = perecheModif;
		syncPereche(indexModif, perecheModif);
	}
}
void removeCheie()
{
	int indexModif;
	cout << endl
		 << "Introdu index elev" << endl
		 << flush;
	cin >> indexModif;
	c11F[indexModif].areCheie = 0;
	c11F[indexModif].nrDulap = 0;
	if (c11F[indexModif].pereche != 0)
	{
		syncPereche(indexModif, c11F[indexModif].pereche);
		c11F[c11F[indexModif].pereche].pereche = 0;
		c11F[indexModif].pereche = 0;
	}
}

void zeroAll(int i)
{
	if (i <= n)
	{
		c11F[i].areCheie = 0;
		c11F[i].nrDulap = 0;
		c11F[i].pereche = 0;
		zeroAll(i + 1);
	}
}
void markNone()
{
	cout << "Introdu index elev" << endl
		 << flush;
	int elev;
	cin >> elev;
	c11F[elev].areCheie = 2;
}

void showNoKey(int i)
{
	if (i == 1)
	{
		cls();
		cout << right << setw(strlen("Index")) << "Index " << left << setw(nameLenMax) << "Nume " << right << setw(strlen("Are cheie")) << "Are cheie " << setw(strlen("Nr. dulap")) << "Nr. dulap " << setw(strlen("Pereche")) << "Pereche" << '\n'
			 << flush;
	}
	if (i <= n)
	{
		if (c11F[i].areCheie == 0)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << right << setw(strlen("Index")) << i << " " << flush;
			cout << left << setw(nameLenMax) << c11F[i].nume << flush;
			cout << right << setw(strlen("Are cheie")) << c11F[i].areCheie << flush;
			cout << right << setw(strlen("Nr. dulap")) << '-' << flush;
			cout << right << setw(strlen("Pereche")) << "-" << '\n'
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
		 << "1. Adauga cheie" << endl
		 << "2. Scoate cheie" << endl
		 << "3. Nu a primit cheie" << endl
		 << "4. Arata cine nu a adus" << endl
		 << "5. Write and exit" << endl
		 << flush;
}
int opt;
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
			addCheie();
		}
		else if (opt == 2)
		{
			removeCheie();
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
