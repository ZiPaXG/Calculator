#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

void parsingExpression(std::vector<std::string>& expressionInVect, std::string expression); // Разбиение строки на элементы vector
bool checkBrackets(std::vector<std::string> expressionInVect);
float calculate(std::vector<std::string> expressionInVect);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string expression;  // Строка с выражением
	std::vector<std::string> expressionInVect; // Вектор с элементами мат. выражения
	std::map<char, std::function<float(float, float)>> operations; // Словарь для определения операций

	// Объявление операций
	operations['+'] = [](float a, float b) { return a + b; };
	operations['-'] = [](float a, float b) { return a - b; };
	operations['*'] = [](float a, float b) { return a * b; };
	operations['/'] = [](float a, float b) { 
		if (b == 0)
			throw std::runtime_error("Divide by zero!");
		return a / b;
	};

	std::cout << "Введите мат. выражение (без пробелов): " << std::endl;

	// Парсинг элементов и проверка корректности скобок
	while (true)
	{
		std::cin >> expression;

		parsingExpression(expressionInVect, expression);

		if (!checkBrackets(expressionInVect))
		{
			std::cout << "Неккорректно введены скобки! Повторите ввод: " << std::endl;
			expressionInVect.clear();
		}
		else
			break;
	}

	// Подсчет выражения

}

void parsingExpression(std::vector<std::string>& expressionInVect, std::string expression)
{
	int countSymbols = 0; // Счетчик символов. Если будет два символа подряд - ошибка
	for (char sym : expression)
	{
		expressionInVect.push_back(std::string(1, sym));
	}
}

bool checkBrackets(std::vector<std::string> expressionInVect)
{
	int counterBrackets = 0; // Счетчик скобок. Если будет отрицательное число - неправильно проставлены скобки

	for (std::string sym : expressionInVect)
	{
		if (counterBrackets < 0)
			return false;

		if (sym == "(")
			counterBrackets++;
		else if (sym == ")")
			counterBrackets--;
	}

	return counterBrackets == 0;
}

float calculate(std::vector<std::string> expressionInVect)
{
	for (std::string sym : expressionInVect)
	{
		
	}
	return 0;
}
