#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class GraphInterpretator
{
public:
	int S = 0;
	vector<bool> conditions;

	GraphInterpretator();
	
	string toBinary(int num);
	void printState(vector<int> yb);
	void nextStep(int& S, vector<bool>& xb);
	void v14Murav2(int startS, vector<bool> xb);
};

