#include "GraphInterpretator.h"

GraphInterpretator::GraphInterpretator()
{

}

std::string GraphInterpretator::toBinary(int n)
{
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}

void GraphInterpretator::printState(vector<int> yb)
{
	cout << "Состояние: S" << S << "   ";
	cout << "Состояния a(1..4): " << setfill('0') << setw(4) << toBinary(S) << "   ";
	cout << "Состояния y(1..15):";
	for (int x = 0; x < yb.size(); x++)
		cout << " y" << yb[x];
	cout << "   ";

	string binY = string(15, '0');
	for (int x = 0; x < yb.size(); x++)
		binY[yb[x] - 1] = '1';

	cout << "Состояния бинарные y(1..15):" << binY << "   ";
	cout << endl;
}

void GraphInterpretator::nextStep(int& S, vector<bool>& xb)
{
	if (S == 0)
	{
		printState({});
		S = 1;
		return;
	}

	if (S == 1)
	{
		printState({ 1 });
		if (!xb[1] && (xb[3] || xb[2]))
			S = 3;
		else
			S = 2;
		return;
	}

	if (S == 2)
	{
		printState({ 2 });
		S = 4;
		return;
	}

	if (S == 3)
	{
		printState({ 3, 4 });
		if (xb[5])
			S = 6;
		else
			S = 7;
		return;
	}

	if (S == 4)
	{
		printState({ 5 });
		if (xb[4])
			S = 5;
		else
			S = 14;
		return;
	}

	if (S == 5)
	{
		printState({ 6, 4 });
		if (xb[6])
			S = 9;
		else
			S = 8;
		return;
	}

	if (S == 6)
	{
		printState({ 7 });
		S = 7;
		return;
	}

	if (S == 7)
	{
		printState({ 8, 9, 10 });
		if (xb[7] && xb[2] && xb[9])
			S = 12;
		else if (!xb[7] && xb[5])
			S = 6;
		else if (!xb[7] && !xb[5])
			S = 7;
		else if (xb[7] && !xb[2] && xb[4])
			S = 11;
		else if (xb[7] && !xb[2] && !xb[4])
			S = 14;
		else if (xb[7] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 13;
		else if (xb[7] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 0;
		return;
	}

	if (S == 8)
	{
		printState({ 5 });
		S = 10;
		return;
	}

	if (S == 9)
	{
		printState({ 7 });
		S = 10;
		return;
	}

	if (S == 10)
	{
		printState({ 11, 6, 10 });
		if (xb[7])
			S = 11;
		if (!xb[7] && xb[6])
			S = 9;
		if (!xb[7] && !xb[6])
			S = 8;
		return;
	}

	if (S == 11)
	{
		printState({ 12 });
		if (xb[1] && xb[8])
			S = 12;
		if (!xb[1] && xb[2] && xb[9])
			S = 12;
		if (xb[1] && !xb[8] && (xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 13;
		if (!xb[1] && !xb[2] && (xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 13;
		if (!xb[1] && xb[2] && !xb[9] && (xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 13;
		if (xb[1] && !xb[8] && !(xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 0;
		if (!xb[1] && !xb[2] && !(xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 0;
		if (!xb[1] && xb[2] && !xb[9] && !(xb[10] && !xb[11] || !xb[10] && xb[11]))
			S = 0;
		return;
	}

	if (S == 12)
	{
		printState({ 13 });
		if (xb[10] && !xb[11] || !xb[10] && xb[11])
			S = 13;
		else
			S = 0;
		return;
	}

	if (S == 13)
	{
		printState({ 14 });
		S = 0;
		return;
	}

	if (S == 14)
	{
		printState({ 15 });
		S = 0;
		return;
	}
}

void GraphInterpretator::v14Murav2(int startS, vector<bool> xb)
{
	conditions = vector<bool>(15, false);
	S = startS;

	while (!conditions[S])
	{
		conditions[S] = true;
		nextStep(S, xb);
	}

	int tempS = S;

	nextStep(S, xb);

	if (tempS == 0)
		cout << "Алгортим завершил работу" << endl;
	else
		cout << "Алгоритм зациклился на состоянии " << tempS << endl;
}
