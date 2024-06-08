#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>

bool parsingExpression(std::vector<std::string>& expressionInVect, std::string expression); // Разбиение строки на элементы vector
bool checkBrackets(std::vector<std::string> expressionInVect); // Проверка на корректность скобок
void calculate(std::vector<std::string>& expressionInVect); // Вычисление выражения

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

		if (!parsingExpression(expressionInVect, expression))
		{
			std::cout << "Неккорректно введено выражение! Повторите ввод: " << std::endl;
			expressionInVect.clear();
			continue;
		}

		if (!checkBrackets(expressionInVect))
		{
			std::cout << "Неккорректно введены скобки! Повторите ввод: " << std::endl;
			expressionInVect.clear();
			continue;
		}

		break;
	}

	// Контрольная проверка
	for (std::string str : expressionInVect)
		std::cout << str << std::endl;


	// Подсчет выражения
	//calculate(expressionInVect);
}

#include <vector>
#include <string>

bool parsingExpression(std::vector<std::string>& expressionInVect, std::string expression) {
	std::string string_nums;
	const std::string symbols = "+-*/().1234567890"; // Допустимые символы

	bool expectNum = true;

	for (int i = 0; i < expression.size(); ++i) {
		char sym = expression[i];

		if (symbols.find(sym) == std::string::npos)
			return false;

		if (isdigit(sym)) {
			string_nums.push_back(sym);
			expectNum = false;
		}

		else {
			// Обработка отрицательных чисел
			if (sym == '-' && expectNum) {
				string_nums.push_back(sym);
			}
			else {
				if (!string_nums.empty()) {
					expressionInVect.push_back(string_nums);
					string_nums.clear();
				}
				expressionInVect.push_back(std::string(1, sym));
				expectNum = (sym != ')');
			}
		}
	}

	// Сохранение последнего накопленного числа
	if (!string_nums.empty()) {
		expressionInVect.push_back(string_nums);
	}

	return true;
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

void calculate(std::vector<std::string>& expressionInVect)
{
	for (std::string sym : expressionInVect)
	{
		
	}
}
