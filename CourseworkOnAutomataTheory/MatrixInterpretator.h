#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class MatrixInterpretator
{
public:
	int countA = 4;
	int countX = 11;
	vector<vector<string>> yb, w, u;
	vector<bool> conditions;

	MatrixInterpretator(int countY, int countWU);

	vector<string> split(string s, string delimiter);
	void updateCharachterOfExpression(char c, bool& isLastDigit, int& id, string& num, string& row, char& bit);
	string get_row(string& expression, int countA, int countX);

	string toBinary(int n);
	int toDec(string bin);

	vector<vector<string>> loadMatrices(string path);

	bool compareRows(string input, string comparator);
	bool compareRowWithMatrix(string input, vector<string> matrix);

	string changeA(string a, string row);
	void printState(int S, string row);
	string getRow(int S, vector<bool>& xb);

	int nextStep(int S, vector<bool>& xb);
	void v14Murav2(vector<bool> xb);
};

