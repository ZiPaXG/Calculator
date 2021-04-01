// Умный калькулятор.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

string* del_func(string* x, const int v);
//void priravn(string a, int* b[], string* x[], int j, int i);

//void opred_znaka(string a, string* x[], int j)
//{
//	for (int i = 0; i < j; i++)
//	{
//		if (a[i] == '(')
//		{
//			*x[i] = "1";
//		}
//
//		else if (a[i] == ')')
//		{
//			*x[i] = "2";
//		}
//
//		else if (a[i] == '*' || a[i] == '/')
//		{
//			*x[i] = "3";
//		}
//
//		else if (a[i] == '+' || a[i] == '-')
//		{
//			*x[i] = "4";
//		}
//
//		else
//		{
//			*x[i] = "0";
//		}
//	}
//}

//void opred_znaka(string a, int* b[], string* x[], int j)
//{
//	int c = 0;
//	int f = 0;
//	int f1 = 0;
//
//	for (int i = f; i < j; i++)
//	{
//		if (*x[i] == "0" && c == 0)
//		{
//			c += 1;
//			f = i;
//		}
//		
//		else if (*x[i] == "0")
//		{
//			c += 1;
//		}
//		
//		else
//		{
//			f1 = i-1;
//			break;
//		}
//	}
//	
//	for (int i = f; i < f1; i++)
//	{
//		string v[50] = {};
//		v[i] += a[i];
//	}
//}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string a; //строка
	string b; //строка буфер
	int n = 0;
	int v = 1; // изначальный размер массива

	cout << "Введите выражение(без пробелов): " << endl;
	getline(cin, a);

	int j = a.size();
	string* x = new string[v];
	for (int i = 0; i < j; i++)
	{
		if (a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-')
		{
			b.push_back(a[i]);
		}

		else if (i == j - 1 && a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-')
		{
			b.push_back(a[i]);
			x[n] = b;
			b.clear();
			break;
		}

		else if (i == j - 1 && a[i] == '(' || a[i] == ')' || a[i] == '*' || a[i] == '/' || a[i] == '+' || a[i] == '-')
		{
			x[n] = b;
			n += 1;
			x[n] = a[i];
			break;
		}

		else
		{
			x[n] = b;
			b.clear();
			n += 1;
			x = del_func(x, v);
			v++;
			x[n] = a[i];
			n += 1;
			x = del_func(x, v);
			v++;
		}
	}
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

//void opred_znaka(string a, int* b[], string* x[], int j)
//{
//	for (int i = 0; i < j; i++)
//	{
//		//priravn(a, b, x, j, i);
//		if (a[i] == '*')
//		{
//			*x[i] = "*";
//		}
//		
//		/*else
//		{
//			*b[i] = (int)a[i] - (int)'0';
//		}*/
//	}
//
//}

//void priravn(string a, int* b[], string* x[], int j, int i)
//{
//	switch (a[i])
//	{
//	case '*':
//		*x[i] = "*";
//		break;
//	case '/':
//		*x[i] = "/";
//		break;
//	case '+':
//		*x[i] = "+";
//		break;
//	case '-':
//		*x[i] = "-";
//		break;
//	case '(':
//		*x[i] = "(";
//		break;
//	case ')':
//		*x[i] = ")";
//		break;
//	default:
//		*b[i] = (int)a[i] - (int)'0';
//		break;
//	}
//}
//Приоретет: 
//1 - Скобки
//2 - Умножение или деление
//3 - сложение или вычитание
//n = (int)a[0] - (int)'0';  перевод из строки в число