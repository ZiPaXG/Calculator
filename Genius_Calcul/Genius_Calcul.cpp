// Умный калькулятор.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

string* parsing(int j, int& v, int n, string* x, string b, string a);
string* del_func(string* x, const int v);
void check_skob(string* x, int v, int c, int z);
void plus_mas(string** mas, const int с, const int z);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string a;  // строка
	string b;  // строка буфер
	int n = 0; // счетчик для массива в ф-ции del_func
	int v = 1; // изначальный размер массива
	int c = 2; // строки
	int z = 2; // столбцы

	cout << "Введите выражение(без пробелов): " << endl;
	getline(cin, a);

	int j = a.size();
	string* x = new string[v];
	x = parsing(j, v, n, x, b, a);
	check_skob(x, v, c, z);
	
}

string* parsing(int j, int& v, int n, string* x, string b, string a)
{
	for (int i = 0; i < j; i++)
	{
		if (a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-')
		{
			if (i < j - 1)
				b.push_back(a[i]);
			else
			{
				b.push_back(a[i]);
				x[n] = b;
				b.clear();
			}
		}

		else
		{
			x[n] = b;
			b.clear();
			x = del_func(x, v);
			v++;
			n++;
			x[n] = a[i];
			x = del_func(x, v);
			v++;
			n++;
		}
	}
	return x;
}

string* del_func(string* x, const int v)
{
	//создание нового массива
	string* mas = new string[v + 1];
	//копирование
	for (int i = 0; i < v; i++)
	{
		mas[i] = x[i];
	}
	//прибавление размера на 1
	delete[]x;
	//копирование из буффера в нужный массив
	x = mas;
	return x;
}

void check_skob(string* x, int v, int c, int z)
{
	string** mas = new string*[c];
	int n = 0;
	for (int i = 0; i < c; i++)
	{
		mas[i] = new string[z];
	}
	
	//for (int i = 0; i < z; i++)
	//{
	//	for (int j = 0; j < c; j++)
	//	{
	//		mas[i][j] = '0';
	//		cout << mas[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	for (int i = 0; i < v; i++)
	{
		
		if (n > 0 && x[i] == "(")
		{
			mas[n][n - n] = i;
			cout << mas[n][n - n] << endl;
			plus_mas(mas, c, z);
		}
		
		else if (n == 0 && x[i] == "(")
		{
			mas[n][n] = i;
			n++;
		}
		
	}
}

void plus_mas(string** mas, const int c, const int z)
{
	//создание нового массива
	string** mas1 = new string*[c + 1];
	for (int i = 0; i < c + 1; i++)
	{
		mas[i] = new string[z + 1];
	}
	
	//копирование
	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < c; j++)
		{
			mas1[i][j] = mas[i][j];
		}
	}
	
	//прибавление размера на 1
	for (int i = 0; i < c; i++)
	{
		delete[]mas[i];
	}
	delete[]mas;
	
	//копирование из буффера в нужный массив
	mas = mas1;
}
//Приоретет: 
//1 - Скобки
//2 - Умножение или деление
//3 - сложение или вычитание
//n = (int)a[0] - (int)'0';  перевод из строки в число