// Умный калькулятор.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

void opred_znaka(string a, int* b[], string* x[], int j);
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

	cout << "Введите выражение(без пробелов): " << endl;
	getline(cin, a);

	int j = a.size();
	string* x = new string[j];
	for (int i = 0; i < j; i++)
	{
		if (a[i] != '(' && a[i] != ')' && a[i] != '*' && a[i] != '/' && a[i] != '+' && a[i] != '-')
		{
			b.push_back(a[i]);
			cout << b << endl;
		}
		
		else
		{
			n++;
			x[n] = b;
			b.clear();
			cout << x[n] << endl;
			n++;
		}
	}
}

void opred_znaka(string a, int* b[], string* x[], int j)
{
	for (int i = 0; i < j; i++)
	{
		//priravn(a, b, x, j, i);
		if (a[i] == '*')
		{
			*x[i] = "*";
		}
		
		/*else
		{
			*b[i] = (int)a[i] - (int)'0';
		}*/
	}

}

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