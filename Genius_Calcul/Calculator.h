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
	std::string expression;  // ������ � ����������
	std::vector<std::string> expressionInVect; // ������ � ���������� ���. ���������

public:
	~Calculator();
	void setExpression(std::string expression);
	bool parsingExpression(std::vector<std::string>& expressionInVect, std::string expression); // ��������� ������ �� �������� vector
	bool checkBrackets(const std::vector<std::string> expressionInVect); // �������� �� ������������ ������
	void evaluationExpression(std::vector<std::string>& expressionInVect); // ���������� ���������
	std::pair<int, int> getNestedBracketsPos(std::vector<std::string> expressionInVect); // ����� ����� ��������� ������
	double solveSomeExpression(std::vector<std::string> someExpression); // ������� �������������� ���������
	float calculate();
};