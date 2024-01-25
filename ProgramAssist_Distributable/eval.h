#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<stdexcept>
#include<math.h>
#include"colorCodes.h"


double eval(std::string exp)
{
	int count = 0;
	double res;
	std::vector<double> numbers;
	std::vector<char> op;
	LOG(exp);
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '(')
		{
			int k = i;
			int br = 1;
			while (br > 0)
			{
				i++;
				if (exp[i] == ')')
					br--;
				else if (exp[i] == '(')
					br++;
				if (i == exp.size())
				{
					throw std::runtime_error("brackets not terminated");
					return 0;
				}
			}
			try {
				res = eval(exp.substr(k + 1, i - k - 1));
			}
			catch (std::runtime_error& e)
			{
				ERROR(e.what());
			}
			catch (std::exception& e)
			{
				ERROR(e.what());
			}
			LOG("result obtained " << res);
			try {
				exp.erase(k, i);
				exp.insert(k, std::to_string(res));
			}
			catch (std::exception& e) {
				std::cerr << e.what() << '\n';
			}
			i = 0;
		}
	}
	LOG(exp);

	char* nend;
	char* expc = new char[exp.size()];
	for (int i = 0; i < exp.size(); i++)
		expc[i] = exp[i];
	char* pEnd = expc;
	do {
		numbers.push_back(strtod(pEnd, &nend));
		if (nend - expc != exp.size()) {
			op.push_back(nend[0]);
			pEnd = nend + 1;
		}
	} while (nend - expc < exp.size());

	for (int i = 0; i < op.size(); i++)
	{
		if (op[i] == '^')
		{
			numbers[i] = pow(numbers[i],numbers[i + 1]);
			numbers.erase(numbers.begin() + i + 1);
			op.erase(op.begin() + i);
		}
	}
	for (int i = 0; i < op.size(); i++)
	{
		if (op[i] == '/')
		{
			try {
				numbers[i] = numbers[i] / numbers[i + 1];
				numbers.erase(numbers.begin() + i + 1);
				op.erase(op.begin() + i);
				if (numbers[i + 1] == 0)
					throw std::runtime_error("division by zero");
			}
			catch (const std::exception& e)
			{
				ERROR(e.what());
			}
		}
	}
	for (int i = 0; i < op.size(); i++)
	{
		if (op[i] == '*')
		{
			numbers[i] = numbers[i] * numbers[i + 1];
			numbers.erase(numbers.begin() + i + 1);
			op.erase(op.begin() + i);
		}
	}
	for (int i = 0; i < op.size(); i++)
	{
		if (op[i] == '-')
		{
			numbers[i] = numbers[i] - numbers[i + 1];
			numbers.erase(numbers.begin() + i + 1);
			op.erase(op.begin() + i);
		}
	}
	for (int i = 0; i < op.size(); i++)
	{
		if (op[i] == '+')
		{
			numbers[i] = numbers[i] + numbers[i + 1];
			numbers.erase(numbers.begin() + i + 1);
			op.erase(op.begin() + i);
		}
	}
	return numbers.back();
}

std::string valid(char a)
{
	std::string rv;
	if ((a > 47 && a < 58) || (a > 64 && a < 91) || a == 95 || (a > 96 && a < 123))
		rv = a;
	else if (a == 32)
		rv = '_';
	else {
		rv = "chr(" + std::to_string(int(a)) + ")";
	}
	return rv;
}