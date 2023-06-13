#include <iostream>
#include "LogicInterpretator.h"
#include "GraphInterpretator.h"
#include "MatrixInterpretator.h"
#include <chrono>
#include <windows.h>

void startMatrixInterpretator(vector<bool>& xb)
{
	cout << "Матричный интерпретатор" << endl;
	MatrixInterpretator matrixInterpretator(15, 4);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	matrixInterpretator.v14Murav2(xb);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	cout << "Время работы автомата: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
}

void startGraphInterpretator(vector<bool>& xb)
{
	cout << "Графовый интерпретатор" << endl;
	GraphInterpretator graphInterpretator;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	graphInterpretator.v14Murav2(0, xb);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	cout << "Время работы автомата: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
}

int main()
{

	setlocale(0, "ru");
	//
	vector<bool> test1 = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0 }; //S0 S1 S3 S6 S7 S12 S13 S0 ++
	vector<bool> test2 = { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //S0 S1 S3 S7 S7 ++
	vector<bool> test3 = { 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 }; //S0 S1 S2 S4 S5 S8 S10 S11 S12 S0 ++
	vector<bool> test4 = { 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 }; //S0 S1 S2 S4 S5 S9 S10 S9 ++
	vector<bool> test5 = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //S0 S1 S2 S4 S14 S0 ++
	vector<bool> test6 = { 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 }; //S0 S1 S2 S4 S5 S9 S10 S11 S12 S0 ++
	vector<bool> test7 = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0 }; //S0 S1 S3 S6 S7 S13 S0 ++
	vector<bool> test8 = { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 }; //S0 S1 S3 S7 S14 S0 ++
	vector<bool> test9 = { 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 }; //S0 S1 S3 S6 S7 S6 ++
	vector<bool> test10 = { 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0 }; //S0 S1 S3 S7 S11 S0 ++

	//01101010110 +
	//01000000000 +
	//10010011000 +
	//10010100000 +
	//10000000000 +
	//10011111111 +
	//01101010010 +
	//00100010000 +
	//00101000000 +
	//00110010000 +

	vector<bool> xb = vector<bool>(11 + 1);
	string xbstring;
	bool isBin;
	do
	{
		isBin = true;
		cout << "Введите значиние x-ов: ";
		cin >> xbstring;

		for (int x = 0; x < xbstring.length(); x++)
			if (!(xbstring[x] == '0' || xbstring[x] == '1'))
			{
				isBin = false;
				break;
			}

		if (!isBin)
			cout << "Введено не бинарное число." << endl << endl;
		else if (xbstring.length() != xb.size() - 1)
			cout << "Количество введённых знаков не соответствует количеству x-ов (должно быть 11 знаков)." << endl << endl;
		else if (xbstring[0] == '1' && (xbstring[1] == '1' || xbstring[2] == '1'))
			cout << "Нельзя вводить одновременно x1 и хотя бы одно из значений x2 или x3." << endl << endl;
		else if (xbstring[0] == '0' && xbstring[1] == '0' && xbstring[2] == '0')
			cout << "Хотя бы одно из значений x1, x2 или x3 должно быть равно 1." << endl << endl;
		

	} while (xbstring.length() != xb.size() - 1 || 
		!isBin || 
		(xbstring[0] == '1' && (xbstring[1] == '1' || xbstring[2] == '1')) || 
		(xbstring[0] == '0' && xbstring[1] == '0' && xbstring[2] == '0'));

	for (int x = 1; x < xb.size(); x++)
		xb[x] = xbstring[x - 1] == '1' ? 1 : 0;

	cout << endl;

	string choose = "";
	while (choose != "1" && choose != "2")
	{
		cin.clear();
		cout << "Выберете интерпретатор: " << endl;
		cout << "1. Матричный интерпретатор" << endl;
		cout << "2. Графовый интерпретатор" << endl;
		cout << "Ваш выбор: ";
		cin >> choose;

		if (choose != "1" && choose != "2")
			cout << "Веденно некорректно значение." << endl << endl;
	}
	cout << "====================" << endl;
	cout << endl;

	switch (stoi(choose))
	{
	case 1:
	{
		startMatrixInterpretator(xb);
		break;
	}
	case 2: 
	{
		startGraphInterpretator(xb);
		break;
	}
	}
}