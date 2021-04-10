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
string* min_func(string* x, const int v, int a, int z);
void check_skob(string* x, int v, int m);
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

string* min_func(string* c, const int b, int a, int z)
{
	//создание нового массива
	string* mas = new string[b - 2];
	int n = 0;
	
	//копирование
	for (int i = 0; i < b; i++)
	{
		if (i == z && b-2 == 1)
		{
			mas[n] = to_string(a);
			cout << mas[n] << endl;
			break;
		}
		
		else if (i == z)
		{
			mas[n] = to_string(a);
			cout << mas[n] << endl;
			n++;
			i += 2;
		}

		else
		{
			mas[n] = c[i];
			cout << mas[n] << endl;
			n++;
		}
	}
	//удаление элементов массива c
	delete[]c;
	//копирование из буффера в нужный массив
	c = mas;
	return c;
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
}

void proverka(string* x, int v, int x1, int x2, int m)
{
	int a = 0;
	int b = 0;
	int z = 0;
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
	
	for (int i = 0; i < sizeof(c); i++) // проверка знака умножения и деления
	{
		if (c[i] == "*")
		{
			a = stoi(c[i - 1]) * stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			if (i == sizeof(c) - 1)
			{
				break;
			}
			
			else
			{
				i = 0;
			}
		}

		else if (c[i] == "/")
		{
			a = stoi(c[i - 1]) / stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			if (i == sizeof(c) - 1)
			{
				break;
			}

			else
			{
				i = 0;
			}
		}
	}

	for (int i = 0; i < sizeof(c); i++) // проверка знака сложения и вычитания 
	{
		if (c[i] == "+")
		{
			a = stoi(c[i - 1]) + stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			if (i == sizeof(c) - 1)
			{
				break;
			}

			else
			{
				i = 0;
			}
		}
		else if (c[i] == "-")
		{
			a = stoi(c[i - 1]) - stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			if (i == sizeof(c) - 1)
			{
				break;
			}

			else
			{
				i = 0;
			}
		}

	}
}
//	for (int i = x1 + 1; i < x2; i++) // проверка знака
//	{
//		if (c[i] == "*")
//		{
//			a = stoi(x[i - 1]) * stoi(x[i + 1]); // идет подсчет выражения
//			z = i - 1; // координата числа для замены вместо выражения
//			c = min_func(c, b, a, z, x1, x2); // ф-ция
//			cout << c[0] << endl;
//		}
//
//		else if (c[i] == "/")
//		{
//			a = stoi(x[i - 1]) / stoi(x[i + 1]);
//			z = i - 1;
//			c = min_func(c, b, a, z, x1, x2);
//			cout << sizeof(c) << endl;
//			for (int i = 0; i < sizeof(c); i++)
//			{
//				cout << c[i] << endl;
//			}
//		}
//	}
//	
//	for (int i = x1+1; i < x2; i++)
//	{
//		if (c[i] == "+")
//		{
//			a = stoi(x[i - 1]) + stoi(x[i + 1]);
//			z = i - 1;
//			c = min_func(c, b, a, z, x1, x2);
//			cout << sizeof(c) << endl;
//			for (int i = 0; i < sizeof(c); i++)
//			{
//				cout << c[i] << endl;
//			}
//		}
//		else if (c[i] == "-")
//		{
//			a = stoi(x[i - 1]) - stoi(x[i + 1]);
//			z = i - 1;
//			c = min_func(c, b, a, z, x1, x2);
//			cout << sizeof(c) << endl;
//			for (int i = 0; i < sizeof(c); i++)
//			{
//				cout << c[i] << endl;
//			}
//		}
//
//	}
//}