#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>

bool parsingExpression(std::vector<std::string>& expressionInVect, std::string expression); // Разбиение строки на элементы vector
bool checkBrackets(const std::vector<std::string> expressionInVect); // Проверка на корректность скобок
void calculate(std::vector<std::string>& expressionInVect); // Вычисление выражения
std::pair<int, int> getNestedBracketsPos(std::vector<std::string> expressionInVect); // Поиск самой вложенной скобки
double solveSomeExpression(std::vector<std::string> someExpression); // Подсчет промежуточного выражения


std::map<std::string, std::function<float(float, float)>> operations = {
	{"+", std::plus<float>()},
	{"-", std::minus<float>()},
	{"*", std::multiplies<float>()},
	{"/", std::divides<float>()}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string expression;  // Строка с выражением
	std::vector<std::string> expressionInVect; // Вектор с элементами мат. выражения

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
	//for (std::string str : expressionInVect)
	//	std::cout << str << std::endl;


	// Подсчет выражения
	calculate(expressionInVect);

	printf("Результат: %.2f", stof(expressionInVect[0]));
}

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
		if (sym == "(")
			counterBrackets++;
		else if (sym == ")")
			counterBrackets--;
		
		if (counterBrackets < 0)
			return false;
	}

	return counterBrackets == 0;
}

// Подсчет поэтапно:
// 1. Поиск самой вложенной скобки
// 2. Решения выражения в скобке
// 3. Последовательное раскрытие остальных скобок
// 4. Подсчет итогового выражения
void calculate(std::vector<std::string>& expressionInVect)
{
	std::pair<int, int> brackets_pos;
	float temp_result = 0;
	while (expressionInVect.size() > 1)
	{
		brackets_pos = getNestedBracketsPos(expressionInVect);
		if (brackets_pos.first != -1)
		{
			std::vector<std::string> buf_expression(brackets_pos.second - brackets_pos.first - 1);
			std::copy(expressionInVect.begin() + brackets_pos.first + 1, expressionInVect.begin() + brackets_pos.second, buf_expression.begin());
			temp_result = solveSomeExpression(buf_expression);
			expressionInVect.insert(expressionInVect.begin() + brackets_pos.first, std::to_string(temp_result));
			expressionInVect.erase(expressionInVect.begin() + brackets_pos.first + 1, expressionInVect.begin() + brackets_pos.second + 2);
		}
		else
		{
			temp_result = solveSomeExpression(expressionInVect);
			expressionInVect.insert(expressionInVect.begin(), std::to_string(temp_result));
			expressionInVect.erase(expressionInVect.begin() + 1, expressionInVect.end());
		}
	}
}

std::pair<int, int> getNestedBracketsPos(const std::vector<std::string> expressionInVect)
{
	std::pair<int, int> brackets_pos = { -1, -1 };

	for (int i = expressionInVect.size() - 1; i >= 0; i--)
	{
		if (expressionInVect[i] == "(")
		{
			brackets_pos.first = i;
			break;
		}
	}

	if (brackets_pos.first == -1)
		return brackets_pos;

	for (int i = brackets_pos.first; i < expressionInVect.size(); i++)
	{
		if (expressionInVect[i] == ")")
		{
			brackets_pos.second = i;
			return brackets_pos;
		}
	}

	return { -1, -1 };
}

double solveSomeExpression(std::vector<std::string> someExpression)
{
	float result;
	auto performOperation = [&](int i) {
		result = operations[someExpression[i]](stof(someExpression[i - 1]), stof(someExpression[i + 1])); // Округление до 3 знаков после запятой

		someExpression.insert(someExpression.begin() + i - 1, std::to_string(result).substr(0, 4));
		someExpression.erase(someExpression.begin() + i, someExpression.begin() + i + 3);
	};

	auto proccessOperators = [&](const std::vector<std::string> operations) {
		int i = 1;
		while (i < someExpression.size() - 1)
		{
			if (std::find(operations.begin(), operations.end(), someExpression[i]) != operations.end())
			{
				performOperation(i);
				continue;
			}
			i += 2;
		}
	};

	proccessOperators({ "*", "/" });
	proccessOperators({ "+", "-" });

	return stof(someExpression[0]);
}
