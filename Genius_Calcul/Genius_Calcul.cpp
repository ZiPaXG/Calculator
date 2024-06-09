#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>
#include "Calculator.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Calculator calc;
	float result;
	
	result = calc.calculate();
	printf("Результат: %.2f", result);
}
