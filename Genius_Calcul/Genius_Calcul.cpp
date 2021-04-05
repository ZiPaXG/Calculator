// Умный калькулятор.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

string* parsing(int j, int& v, int n, string* x, string b, string a);
string* plus_func(string* x, const int v);
string* min_func(string* x, const int v, int a);
void check_skob(string* x, int v, int m);
void plus_mas(string** mas, const int с, const int z);
void proverka(string* x, int v, int x1, int x2, int m);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string a;  // строка
	string b;  // строка буфер
	int n = 0; // счетчик для массива в ф-ции del_func
	int v = 1; // изначальный размер массива
	int m = 1; // изначальный размер массива ф-ции proverka

	cout << "Введите выражение(без пробелов): " << endl;
	getline(cin, a);

	int j = a.size();
	string* x = new string[v];
	x = parsing(j, v, n, x, b, a);
	check_skob(x, v, m);
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
			x = plus_func(x, v);
			v++;
			n++;
			x[n] = a[i];
			x = plus_func(x, v);
			v++;
			n++;
		}
	}
	return x;
}

string* plus_func(string* x, const int v)
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

string* min_func(string* x, const int v, int a)
{
	//создание нового массива
	string* mas = new string[v - 2];
	
	//копирование
	for (int i = 0; i < v-2; i++)
	{
		if (i == v - 3)
		{
			mas[i] = to_string(a);
		}
		
		else
		{
			mas[i] = x[i];
		}
	}
	//прибавление размера на 1
	delete[]x;
	//копирование из буффера в нужный массив
	x = mas;
	return x;
}

void check_skob(string* x, int v, int m)
{
	int x1 = 0;
	int x2 = 0;

	for (int i = 0; i < v; i++)
	{
		if (x1 != 0 && x2 != 0)
		{
			proverka(x, v, x1, x2, m);
		}
		
		else if (x[i] == "(")
		{
			x1 = i;
		}
		
		else if (x[i] == ")")
		{
			x2 = i;
		}
	}
	//string** mas = new string*[c];
	//int n = 0;
	//for (int i = 0; i < c; i++)
	//{
	//	mas[i] = new string[z];
	//}
	//
	//for (int i = 0; i < z; i++)
	//{
	//	for (int j = 0; j < c; j++)
	//	{
	//		mas[i][j] = '0';
	//		cout << mas[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	//for (int i = 0; i < v; i++)
	//{
	//	
	//	if (n > 0 && x[i] == "(")
	//	{
	//		mas[n][n - n] = i;
	//		cout << mas[n][n - n] << endl;
	//		plus_mas(mas, c, z);
	//	}
	//	
	//	else if (n == 0 && x[i] == "(")
	//	{
	//		mas[n][n] = i;
	//		n++;
	//	}
	//	
	//}
}

void proverka(string* x, int v, int x1, int x2, int m)
{
	int a = 0;
	int b = 0;
	int n = 0; // счетчик
	
	for (int i = x1 + 1; i < x2; i++) // считаем размер массива скобок
	{
		b++;
	}
	
	string* c = new string[b]; // здесь будет выражение, которое находится в скобках
	
	for (int i = x1 + 1; i < x2; i++) // копирование
	{
		c[n] = x[i];
		n++;
	}
	
	n = 0;
	
	for (int i = x1 + 1; i < x2; i++) // проверка знака
	{
		if (x[i] == "*")
		{
			a = stoi(x[i - 1]) * stoi(x[i + 1]);
			c = min_func(c, b, a);
			cout << c[0] << endl;
		}
		
		else if (x[i] == "/")
		{
			a = stoi(x[i - 1]) / stoi(x[i + 1]);
			c = min_func(c, b, a);
			cout << c[0] << endl;
		}
		else if (x[i] == "+")
		{
			a = stoi(x[i - 1]) + stoi(x[i + 1]);
			c = min_func(c, b, a);
			cout << c[0] << endl;
		}
		else if (x[i] == "-")
		{
			a = stoi(x[i - 1]) - stoi(x[i + 1]);
			c = min_func(c, b, a);
			cout << c[0] << endl;
		}

	}
}

//void plus_mas(string** mas, const int c, const int z)
//{
//	//создание нового массива
//	string** mas1 = new string*[c + 1];
//	for (int i = 0; i < c + 1; i++)
//	{
//		mas[i] = new string[z + 1];
//	}
//	
//	//копирование
//	for (int i = 0; i < z; i++)
//	{
//		for (int j = 0; j < c; j++)
//		{
//			mas1[i][j] = mas[i][j];
//		}
//	}
//	
//	//прибавление размера на 1
//	for (int i = 0; i < c; i++)
//	{
//		delete[]mas[i];
//	}
//	delete[]mas;
//	
//	//копирование из буффера в нужный массив
//	mas = mas1;
//}