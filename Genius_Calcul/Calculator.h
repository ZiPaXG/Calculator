#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>

class Calculator
{
	std::map<std::string, std::function<float(float, float)>> operations = {
	{"+", std::plus<float>()},
	{"-", std::minus<float>()},
	{"*", std::multiplies<float>()},
	{"/", std::divides<float>()}
	};
	std::string expression;  // Строка с выражением
	std::vector<std::string> expressionInVect; // Вектор с элементами мат. выражения

public:
	~Calculator();
	void setExpression(std::string expression);
	bool parsingExpression(std::vector<std::string>& expressionInVect, std::string expression); // Разбиение строки на элементы vector
	bool checkBrackets(const std::vector<std::string> expressionInVect); // Проверка на корректность скобок
	void evaluationExpression(std::vector<std::string>& expressionInVect); // Вычисление выражения
	std::pair<int, int> getNestedBracketsPos(std::vector<std::string> expressionInVect); // Поиск самой вложенной скобки
	double solveSomeExpression(std::vector<std::string> someExpression); // Подсчет промежуточного выражения
	float calculate();
};