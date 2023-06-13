#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LogicInterpretator
{
public:
	vector<bool> a, yb, xb, w, u, conditions;

	LogicInterpretator(vector<bool> xb);

	void changeA();
	void updateY();
	void updateW();
	void updateU();

	int toDec(vector<bool> bin);

	string out(vector<bool> bin);
	void printState();

	void nextStep();
	void v14Murav2();
};

