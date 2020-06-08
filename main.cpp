#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct osoba
{
	string imie;
	string nazwisko;
	int wiek;
};

bool comp(osoba a, osoba b)
{
	return a.wiek < b.wiek;
}


class populacja
{
	vector <osoba> tablica;
	fstream plik;
	string napis;
	char znak;

public:
	populacja() {
		plik.open("a.txt", ios::in);
		if (plik.good())
		{
			while (!plik.eof())
			{
				string a, b;
				int c;
				plik >> a >> b >> c;
				if (a != "" && b != "")
					tablica.push_back({ a, b, c });
			}
		}
	}; //otwiera plik i wczytuje dane

	~populacja() {
		plik.close();
	}; // zamyka plik wejściowy

	void sortuj() {
		sort(tablica.begin(), tablica.end(), comp);
	}; //sortowanie od najmłodszego do najstarszego vector. 

	void wypiszJSON() {
		char x = '#' - 1;
		if (tablica.size() > 0)
		{
			cout << "[\n";
			for (int i = 0; i < tablica.size(); i++)
			{

				cout << " {\n";
				cout << "  " << x << "title" << x << ": " << x << tablica[i].imie << " " << tablica[i].nazwisko << x << ",\n";
				cout << "  " << x << "subtitle" << x << ": " << tablica[i].wiek << "\n";
				cout << " }";
				if (i + 1 < tablica.size())
					cout << ",";
				cout << "\n";
			}
			cout << "]";
		}
	};//wypisuje vector w postaci JSON
};



int main()
{
	//cout<<"Content-Type: application/json;charset=UTF-8;Access-Control-Allow-Origin: *" << (char)13 << (char)10;
	cout << "Content-Type:application/json;charset=UTF-8" << (char)13 << (char)10;
	populacja P;
	P.sortuj();
	P.wypiszJSON();
	return 0;
}
