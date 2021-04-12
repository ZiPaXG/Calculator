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
string* min_func(string* c, const int b, int a, int z);
string check_skob(string* x, int v, string m, int b, int* x1, int* x2);
string proverka(string* x, int v, int* x1, int* x2, string m, int b);
string* min_sum(string* x, const int v, string m, int b1, int *x1);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string a;  // строка
	string b;  // строка буфер
	int b1 = 0;
	int x1 = 0; // координата начала скобки
	int x2 = 0;
	int n = 0; // счетчик для массива в ф-ции del_func
	int v = 1; // изначальный размер массива
	string m; // изначальный размер массива ф-ции proverka

	cout << "Введите выражение(без пробелов): " << endl;
	getline(cin, a);

	int j = a.size();
	string* x = new string[v];
	x = parsing(j, v, n, x, b, a);
	m = check_skob(x, v, m, b1, &x1, &x2);
	b1 = x2 - x1;
	cout << v << endl;
	/*x = min_sum(x, v, m, b1, &x1);*/
}

string* parsing(int j, int& v, int n, string* x, string b, string a)
{
	for (int i = 0; i < j; i++)
	{
		if (a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-')
		{
			if (i < j - 1)
			{
				b.push_back(a[i]);
			}

			else
			{
				b.push_back(a[i]);
				x[n] = b;
				b.clear();
			}
		}

		else if ((a[i] == '(' || a[i] == ')' || a[i] == '*' || a[i] == '/' || a[i] == '+' || a[i] == '-') && (a[i + 1] == '(' || a[i + 1] == ')' || a[i + 1] == '*' || a[i + 1] == '/' || a[i + 1] == '+' || a[i + 1] == '-'))
		{
			x[n] = a[i];
			x = plus_func(x, v);
			n++;
			v++;
			x[n] = a[i + 1];
			x = plus_func(x, v);
			i++;
			n++;
			v++;
		}

		else if (i == j - 1)
		{
			x[n] = a[i];
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
			n++;
			v++;
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
	
	for (int i = 0; i < b; i++)
	{
		if (b == 3 && i == z)
		{
			mas[0] = to_string(a);
			cout << mas[0] << endl;
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

string check_skob(string* x, int v, string m, int b, int* x1, int* x2)
{
	for (int i = 0; i < v; i++)
	{
		if (*x1 != 0 && *x2 != 0)
		{
			m = proverka(x, v, x1, x2, m, b);
		}
		
		else if (x[i] == "(")
		{
			*x1 = i;
		}
		
		else if (x[i] == ")")
		{
			*x2 = i;
		}
	}
	
	return m;
}

string proverka(string* x, int v, int* x1, int* x2, string m, int b)
{
	int a = 0;
	int z = 0;
	int n = 0; // счетчик

	for (int i = *x1 + 1; i < *x2; i++) // считаем размер массива скобок
	{
		b++;
	}
	string* c = new string[b]; // здесь будет выражение, которое находится в скобках
	
	for (int i = *x1 + 1; i < *x2; i++) // копирование
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
			i = 0;
			b -= 2;
		}

		else if (c[i] == "/")
		{
			a = stoi(c[i - 1]) / stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			i = 0;
			b -= 2;
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
			i = 0;
			b -= 2;
		}
		
		else if (c[i] == "-")
		{
			a = stoi(c[i - 1]) - stoi(c[i + 1]); // идет подсчет выражения
			z = i - 1; // координата числа для замены вместо выражения
			c = min_func(c, b, a, z); // ф-ция
			a = 0;
			i = 0;
			b -= 2;
		}

	}
	m = c[0];
	return m;
}

//string* min_sum(string* x, const int v, string m, int b1, int* x1)
//{
//	//создание нового массива
//	string* mas = new string[v - 2];
//	
//}