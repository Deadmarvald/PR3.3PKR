#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Windows.h"

using namespace std;

struct Note
{
	string secondname;
	string name;
	int phonenum;
	int date[3];
};

void Create(Note* n, const int N);
void Print(Note* n, const int N);
void Sort(Note* n, const int N);
int Search(Note* n, const int N,const string secondname);
void PrintSearch(Note* n, const int N, const int found);
void SaveToFile(Note* n, const int N, const char* filename);
void LoadFromFile(Note*& n, int& N, const char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;

	cout << "Введіть кількість людей: "; cin >> N;

	Note* n = new Note[N];

	char filename[100];
	string secondname;
	int found;

	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << "\t[1] - Введення даних з клавіатури" << endl;
		cout << "\t[2] - Вивід даних на екран" << endl;
		cout << "\t[3] - Фізичне впорядкування даних за номером телефону" << endl;
		cout << "\t[4] - Пошук інформації про людину за прізвищем" << endl;
		cout << "\t[5] - запис даних у файл" << endl;
		cout << "\t[6] - зчитування даних із файлу" << endl << endl;
		cout << "\t[0] - Exit" << endl << endl;
		cout << "Ваш вибір: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(n, N);
			break;
		case 2:
			Print(n, N);
			break;
		case 3:
			Sort(n, N);
			break;
		case 4:
			cout << "Введіть інформацію для пошуку: " << endl;

			cin.get();
			cin.sync();

			cout << "\tПрізвище: "; getline(cin, secondname);
			cout << endl;
			if ((found = Search(n, N,secondname)) != -1)
			{
				PrintSearch(n, N, found);
			}
			else
			{
				cout << "Шуканої інформації не знайдено" << endl;
			}
			break;
		case 5:
			cin.get();
			cin.sync();

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(n, N, filename);
			break;
		case 6:
			cin.get();
			cin.sync();

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(n, N, filename);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення!\n"
				    "Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	system("pause");
	return 0;
}

void Create(Note* n, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "Людина № " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << "Прізвище: "; getline(cin, n[i].secondname);
		cout << "Ім\'я: "; getline(cin, n[i].name);
		cout << "Номер телефону: +380"; cin >> n[i].phonenum;
		cout << "День народження: "; cin >> n[i].date[0];
		cout << "Місяць народження: "; cin >> n[i].date[1];
		cout << "Рік народження: "; cin >> n[i].date[2];
		cout << endl;
	}
}

void Print(Note* n, const int N)
{
	cout << "================================================================="
		<< endl;
	cout << "| № |   Прізвище   |  Ім\'я  | Номер телефону | День народження  |"
		<< endl;
	cout << "-----------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << n[i].secondname << " ";
		cout << "| " << setw(6) << right << n[i].name << " ";
		cout << "| +380" << setw(10) << left << n[i].phonenum << " ";
		cout << "| " << setw(5) << right << n[i].date[0] << "." << n[i].date[1] << "." << n[i].date[2] << "     |" << endl;
	}
	cout << "================================================================="
		<< endl;
	cout << endl;
}

void Sort(Note* n, const int N)
{
	Note temp;

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - i - 1; j++)
		{
			if (n[j].phonenum > n[j + 1].phonenum)
			{
				temp = n[j];
				n[j] = n[j + 1];
				n[j + 1] = temp;
			}
		}
	}
}

int Search(Note* n, const int N,const string secondname)
{
	int L = 0, R = N - 1, m;

	do {
		m = (L + R) / 2;
		if (n[m].secondname == secondname)
		{
			return m;
		}
		if (n[m].secondname < secondname)
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);

	return -1;
}

void PrintSearch(Note* n, const int N, const int found)
{
	cout << "================================================================="
		<< endl;
	cout << "| № |   Прізвище   |  Ім\'я  | Номер телефону | День народження  |"
		<< endl;
	cout << "-----------------------------------------------------------------"
		<< endl;

	cout << "| " << setw(1) << right << found + 1 << " ";
	cout << "| " << setw(12) << left << n[found].secondname << " ";
	cout << "| " << setw(6) << right << n[found].name << " ";
	cout << "| +380" << setw(10) << left << n[found].phonenum << " ";
	cout << "| " << setw(5) << right << n[found].date[0] << "." << n[found].date[1] << "." << n[found].date[2] << "     |" << endl;

	cout << "================================================================="
		<< endl;
	cout << endl;
}

void SaveToFile(Note* n, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary);

	fout.write((char*)&N, sizeof(N));

	for (int i = 0; i < N; i++)
	{
		fout.write((char*)&n[i], sizeof(Note));
	}

	fout.close();
}

void LoadFromFile(Note*& n, int& N, const char* filename)
{
	delete[] n;

	ifstream fin(filename, ios::binary);

	fin.read((char*)&N, sizeof(N));

	n = new Note[N];

	for (int i = 0; i < N; i++)
	{
		fin.read((char*)&n[i], sizeof(Note));
	}

	fin.close();
}