// Умный калькулятор.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

string* parsing(int j, int& v, int n, string* x, string b, string a); // разделение знаков и чисел
string* plus_func(string* x, const int v); // увеличение массива на 1
string* min_func(string* c, const int b, int a, int z); // уменьшение выражения в скобках
string check_skob(string* x, int v, string m, int b, int* x1, int* x2, string& a); // ищем координаты скобок
string proverka_skob(string* x, int v, int* x1, int* x2, string m, int b); // считаем скобку
string* min_sum(string* x, const int v, string m, int b1, int *x1); // удаляем выражение со скобкой
void proverka(string* x, int v, int b1, int* y); // считаем оставшиеся числа

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string a;  // строка
	string b;  // строка буфер
	int b1 = 0;
	int x1 = -1; // координата начала скобки
	int x2 = -1; // координата конца скобки
	int n = 0; // счетчик для массива в ф-ции del_func
	int v = 1; // изначальный размер массива
	int s1 = 0; //первая скобка
	int s2 = 0; //вторая скобка
	int y = 0;
	int j = 0;
	string m; // изначальный размер массива ф-ции proverka

	while (true) // проверка на скобку
	{
		cout << "Введите выражение(без пробелов): " << endl;
		getline(cin, a);

		j = a.size();
		for (int i = 0; i < j; i++)
		{
			if (a[i] == '(')
			{
				s1 += 1;
			}
			else if (a[i] == ')')
			{
				s2 += 1;
			}
		}
		
		if (s1 != s2)
		{
			cout << "Вы ввели выражение неправильно!" << endl;
			s1 = 0;
			s2 = 0;
			a = "";
		}

		else
		{
			break;
		}
	}
	string* x = new string[v];
	x = parsing(j, v, n, x, b, a);

	if (s1 != 0)
	{
		for (int i = 0; i < s1; i++)
		{
			m = check_skob(x, v, m, b1, &x1, &x2, a);
			b1 = x2 - x1;
			x = min_sum(x, v, m, b1, &x1);	
			v = v - b1 - 1;
			x1 = x2 = -1;
		}
		proverka(x, v, b1, &y);
	}
	
	else
	{
		proverka(x, v, b1, &y);
	}
	cout << "Ответ: " << y << endl;
}

string* parsing(int j, int& v, int n, string* x, string b, string a)
{
	int y2 = 0;
	for (int i = 0; i < j; i++)
	{
		if (a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-') // если это число
		{
			if (i < j - 1) // не последнее
			{
				b.push_back(a[i]);
			}
			
			else // последнее
			{
				b.push_back(a[i]);
				x[n] = b;
				cout << "x[n] " << x[n] << endl;
				b.clear();
			}
		}
		
		else if (a[i] == '(' || a[i] == ')' || a[i] == '*' || a[i] == '/' || a[i] == '+' || a[i] == '-') // если это знак
		{
			if (a[i] == '(')
			{
				x[n] = a[i];
				cout << "x[n] " << x[n] << endl;
				x = plus_func(x, v);
				n++;
				v++;
			}
			
			else
			{
				x[n] = b;
				cout << "x[n] " << x[n] << endl;
				b.clear();
				x = plus_func(x, v);
				n++;
				v++;
				x[n] = a[i];
				cout << "x[n] " << x[n] << endl;
				x = plus_func(x, v);
				n++;
				v++;
			}
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
			break;
		}
	
		else if (i == z)
		{
			mas[n] = to_string(a);
			n++;
			i += 2;
		}

		else
		{
			mas[n] = c[i];
			n++;
		}
	}
	
	//удаление элементов массива c
	delete[]c;
	//копирование из буффера в нужный массив
	c = mas;
	return c;
}

string check_skob(string* x, int v, string m, int b, int* x1, int* x2, string& a)
{
	for (int i = 0; i < v; i++)
	{	
		if (i == v - 1 && x[i] == ")")
		{
			*x2 = i;
			m = proverka_skob(x, v, x1, x2, m, b);
			break;
		}

		else if (*x1 != -1 && *x2 != -1)
		{
			m = proverka_skob(x, v, x1, x2, m, b);
			break;
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

string proverka_skob(string* x, int v, int* x1, int* x2, string m, int b)
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

string* min_sum(string* x, const int v, string m, int b1, int* x1)
{
	int n = 0;
	//создание нового массива
	string* mas = new string[v - b1 - 1];
	for (int i = 0; i < v; i++)
	{
		if (i == *x1)
		{
			mas[n] = m;
			n++;
			i += b1+1;
		}
		
		else
		{
			mas[n] = x[i];
			n++;
		}
	}
	
	delete[]x;
	x = mas;
	return x;
}

void proverka(string* x, int v, int b1, int* y)
{
	int z = 0;
	for (int i = 0; i < v; i++)
	{
		if (x[i] == "*")
		{
			*y = stoi(x[i - 1]) * stoi(x[i + 1]);
			z = i - 1;
			x = min_func(x, v, *y, z);
			v -= 2;
			i = 0;
		}
		else if (x[i] == "/")
		{
			*y = stoi(x[i - 1]) / stoi(x[i + 1]);
			z = i - 1;
			x = min_func(x, v, *y, z);
			v -= 2;
			i = 0;
		}
	}
	
	for (int i = 0; i < v; i++)
	{
		if (x[i] == "+")
		{
			*y = stoi(x[i - 1]) + stoi(x[i + 1]);
			z = i - 1;
			x = min_func(x, v, *y, z);
			v -= 2;
			i = 0;
		}
		else if (x[i] == "-")
		{
			*y = stoi(x[i - 1]) - stoi(x[i + 1]);
			z = i - 1;
			x = min_func(x, v, *y, z);
			v -= 2;
			i = 0;
		}
	}
	*y = stoi(x[0]);
}