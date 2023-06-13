#include "LogicInterpretator.h"

LogicInterpretator::LogicInterpretator(vector<bool> xb)
{
	a = vector<bool>(4 + 1, false);
	w = vector<bool>(4 + 1, false);
	u = vector<bool>(4 + 1, false);
	conditions = vector<bool>(14 + 1, false);

	yb = vector<bool>(15 + 1, false);
	this->xb = vector<bool>(11 + 1, false);

	for (int x = 0; x < this->xb.size(); x++)
		this->xb[x] = xb[x];

	updateY();
}

void LogicInterpretator::changeA()
{
	for (int x = 1; x < a.size(); x++)
	{
		if (w[x])
			a[x] = 1;

		if (u[x])
			a[x] = 0;
	}
}

void LogicInterpretator::updateY()
{
	yb[1] = !a[1] && !a[2] && !a[3] && a[4];
	yb[2] = !a[1] && !a[2] && a[3] && !a[4];
	yb[3] = !a[1] && !a[2] && a[3] && a[4];
	yb[4] = !a[1] && !a[2] && a[3] && a[4] || !a[1] && a[2] && !a[3] && a[4];
	yb[5] = !a[1] && a[2] && !a[3] && !a[4] || a[1] && !a[2] && !a[3] && !a[4];
	yb[6] = !a[1] && a[2] && !a[3] && a[4] || a[1] && !a[2] && a[3] && !a[4];
	yb[7] = !a[1] && a[2] && a[3] && !a[4] || a[1] && !a[2] && !a[3] && a[4];
	yb[8] = !a[1] && a[2] && a[3] && a[4];
	yb[9] = !a[1] && a[2] && a[3] && a[4];
	yb[10] = !a[1] && a[2] && a[3] && a[4] || a[1] && !a[2] && a[3] && !a[4];
	yb[11] = a[1] && !a[2] && a[3] && !a[4];
	yb[12] = a[1] && !a[2] && a[3] && a[4];
	yb[13] = a[1] && a[2] && !a[3] && !a[4];
	yb[14] = a[1] && a[2] && !a[3] && a[4];
	yb[15] = a[1] && a[2] && a[3] && !a[4];
}

void LogicInterpretator::updateW()
{
	w[1] = !a[1] && a[2] && !a[3] && !a[4] && !xb[4] || !a[1] && a[2] && !a[3] && a[4] && xb[6] || !a[1] && a[2] && !a[3] && a[4] && !xb[6] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && xb[9] || !a[1] && a[2] && a[3] && a[4] && xb[7] && !xb[2] && xb[4] || !a[1] && a[2] && a[3] && a[4] && xb[7] && !xb[2] && !xb[4] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]);
	w[2] = !a[1] && !a[2] && a[3] && !a[4] || !a[1] && !a[2] && a[3] && a[4] && xb[5] || !a[1] && !a[2] && a[3] && a[4] && !xb[5] || a[1] && !a[2] && a[3] && a[4] && xb[1] && xb[8] || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && xb[9] || a[1] && !a[2] && a[3] && a[4] && xb[1] && !xb[8] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && !xb[2] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]);
	w[3] = !a[1] && !a[2] && !a[3] && a[4] && !xb[1] && (xb[3] || xb[2]) || !a[1] && !a[2] && !a[3] && a[4] && !(!xb[1] && (xb[3] || xb[2])) || !a[1] && a[2] && !a[3] && !a[4] && !xb[4] || a[1] && !a[2] && !a[3] && !a[4] || a[1] && !a[2] && !a[3] && a[4];
	w[4] = !a[1] && !a[2] && !a[3] && !a[4] || !a[1] && a[2] && !a[3] && !a[4] && xb[4] || !a[1] && a[2] && a[3] && !a[4] || a[1] && !a[2] && a[3] && !a[4] && xb[7] || a[1] && !a[2] && a[3] && !a[4] && !xb[7] && xb[6] || a[1] && a[2] && !a[3] && !a[4] && (xb[10] && !xb[11] || !xb[10] && xb[11]);
}

void LogicInterpretator::updateU()
{
	u[1] = a[1] && !a[2] && a[3] && a[4] && xb[1] && !xb[8] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && !xb[2] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && !a[3] && !a[4] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && !a[3] && a[4] || a[1] && a[2] && a[3] && !a[4];
	u[2] = !a[1] && a[2] && !a[3] && a[4] && xb[6] || !a[1] && a[2] && !a[3] && a[4] && !xb[6] || !a[1] && a[2] && a[3] && a[4] && xb[7] && !xb[2] && xb[4] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && !a[3] && !a[4] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && !a[3] && a[4] || a[1] && a[2] && a[3] && !a[4];
	u[3] = !a[1] && !a[2] && a[3] && !a[4] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && xb[9] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && !a[4] && !xb[7] && xb[6] || a[1] && !a[2] && a[3] && !a[4] && !xb[7] && !xb[6] || a[1] && !a[2] && a[3] && a[4] && xb[1] && xb[8] || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && xb[9] || a[1] && !a[2] && a[3] && a[4] && xb[1] && !xb[8] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && !xb[2] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && xb[1] && !xb[8] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && !xb[2] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && a[3] && !a[4];
	u[4] = !a[1] && !a[2] && !a[3] && a[4] && !(!xb[1] && (xb[3] || xb[2])) || !a[1] && !a[2] && a[3] && a[4] && xb[5] || !a[1] && a[2] && !a[3] && a[4] && !xb[6] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && xb[9] || !a[1] && a[2] && a[3] && a[4] && !xb[7] && xb[5] || !a[1] && a[2] && a[3] && a[4] && xb[7] && !xb[2] && !xb[4] || !a[1] && a[2] && a[3] && a[4] && xb[7] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && !a[3] && a[4] || a[1] && !a[2] && a[3] && a[4] && xb[1] && xb[8] || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && xb[9] || a[1] && !a[2] && a[3] && a[4] && xb[1] && !xb[8] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && !xb[2] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && !a[2] && a[3] && a[4] && !xb[1] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]) || a[1] && a[2] && !a[3] && a[4];
}

int LogicInterpretator::toDec(vector<bool> bin)
{
	int result = 0;
	for (int x = bin.size() - 1; x >= 0; x--)
		result += bin[x] * pow(2, bin.size() - 1 - x);
	return result;
}

string LogicInterpretator::out(vector<bool> bin)
{
	string str = "";
	for (int x = 1; x < bin.size(); x++)
		str += to_string((int)(bin[x]));
	return str;
}

void LogicInterpretator::printState()
{
	int state = toDec(a);
	cout << "Состояние: S" << state << endl;
	cout << "Состояния a(1..4): " << out(a) << endl;
	cout << "Состояния y(1..15):";
	for (int x = 0; x < yb.size() - 1; x++)
		if (yb[x + 1])
			cout << " y" << x + 1;
	cout << endl;

	cout << "Состояния бинарные y(1..15):" << out(yb) << endl;

	cout << endl;
}

void LogicInterpretator::nextStep()
{
	updateW();
	updateU();
	changeA();
	updateY();
}

void LogicInterpretator::v14Murav2()
{
	int state = toDec(a);
	while (!conditions[state])
	{
		conditions[state] = true;
		printState();
		nextStep();
		state = toDec(a);
	}

	printState();
	if (state == 0)
		cout << "Алгортим завершил работу" << endl;
	else
		cout << "Алгоритм зациклился на состоянии " << state << endl;
}