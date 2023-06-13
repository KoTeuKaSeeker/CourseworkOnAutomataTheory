#include "MatrixInterpretator.h"

MatrixInterpretator::MatrixInterpretator(int countY, int countWU)
{
	vector<vector<string>> matrices = loadMatrices("matrix.txt");

	for (int x = 0; x < countY; x++)
		yb.push_back(matrices[x]);

	for (int x = countY; x < countY + countWU; x++)
		w.push_back(matrices[x]);

	for (int x = countY + countWU; x < countY + countWU * 2; x++)
		u.push_back(matrices[x]);

	conditions = vector<bool>(15, false);
}

vector<string> MatrixInterpretator::split(string s, string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

void MatrixInterpretator::updateCharachterOfExpression(char c, bool& isLastDigit, int& id, string& num, string& row, char& bit)
{
	if (!isdigit(c) && isLastDigit)
	{
		id += stoi(num) - 1;
		num = "";
		row[id] = bit;
		bit = '1';
		isLastDigit = false;
	}

	if (c == '^')
		bit = '0';

	if (c == 'a')
		id = 0;

	if (c == 'x')
		id = countA;

	if (isdigit(c))
	{
		num += c;
		isLastDigit = true;
	}
	else
		num = "";
}

string MatrixInterpretator::get_row(string& expression, int countA, int countX)
{
	string row = string(countA + countX, '-');

	char bit = '1';
	string num = "";
	int id = 0;
	bool isLastDigit = false;

	for (char c : expression)
		updateCharachterOfExpression(c, isLastDigit, id, num, row, bit);
	updateCharachterOfExpression(' ', isLastDigit, id, num, row, bit);

	return row;
}

std::string MatrixInterpretator::toBinary(int n)
{
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}

int MatrixInterpretator::toDec(string bin)
{
	int result = 0;
	for (int x = bin.length() - 1; x >= 0; x--)
		result += (bin[x] == '1' ? 1 : 0) * pow(2, bin.length() - 1 - x);
	return result;
}

vector<vector<string>> MatrixInterpretator::loadMatrices(string path)
{
	vector<vector<string>> matrices;
	ifstream reader(path);
	string line;
	while (getline(reader, line))
	{
		int pointer = line.find("= ");
		if (pointer != string::npos)
		{
			matrices.push_back(vector<string>());
			pointer += 2;
			string cons = string(&line[pointer]);

			vector<string> splitedCons = split(cons, " ");
			for (int x = 0; x < splitedCons.size(); x++)
				if (x % 2 == 0)
				{
					string expression = splitedCons[x];
					string row = get_row(expression, countA, countX);
					matrices[matrices.size() - 1].push_back(row);
				}
		}
	}

	return matrices;
}

bool MatrixInterpretator::compareRows(string input, string comparator)
{
	bool isEquel = true;
	for(int x = 0; x < input.size(); x++)
		if (input[x] != comparator[x] && comparator[x] != '-')
		{
			isEquel = false;
			break;
		}

	return isEquel;
}

bool MatrixInterpretator::compareRowWithMatrix(string input, vector<string> matrix)
{
	bool isEquel = false;
	for (int x = 0; x < matrix.size(); x++)
		if (compareRows(input, matrix[x]))
		{
			isEquel = true;
			break;
		}
	return isEquel;
}

string MatrixInterpretator::changeA(string a, string row)
{
	for (int x = 0; x < w.size(); x++)
	{
		if (compareRowWithMatrix(row, w[x]))
			a[x] = '1';

		if (compareRowWithMatrix(row, u[x]))
			a[x] = '0';
	}
	return a;
}

void MatrixInterpretator::printState(int S, string row)
{
	//cout << "Состояние: S" << S << endl;
	//cout << "Состояния a(1..4): " << setfill('0') << setw(4) << toBinary(S) << endl;
	//cout << "Состояния y(1..15):";
	//for (int x = 0; x < yb.size(); x++)
	//	if (compareRowWithMatrix(row, yb[x]))
	//		cout << " y" << x + 1;
	//cout << endl;

	//string binY = string(yb.size(), '0');
	//for (int x = 0; x < yb.size(); x++)
	//	binY[x] = compareRowWithMatrix(row, yb[x]) ? '1' : '0';

	//cout << "Состояния бинарные y(1..15):" << binY << endl;
	//cout << endl;

	cout << "Состояние: S" << S << "   ";
	cout << "Состояния a(1..4): " << setfill('0') << setw(4) << toBinary(S) << "   ";
	cout << "Состояния y(1..15):";
	for (int x = 0; x < yb.size(); x++)
		if (compareRowWithMatrix(row, yb[x]))
			cout << " y" << x + 1;
	cout << "   ";

	string binY = string(yb.size(), '0');
	for (int x = 0; x < yb.size(); x++)
		binY[x] = compareRowWithMatrix(row, yb[x]) ? '1' : '0';

	cout << "Состояния бинарные y(1..15):" << binY << "   ";
	cout << endl;
}

string MatrixInterpretator::getRow(int S, vector<bool>& xb)
{
	stringstream ss;
	ss << setw(w.size()) << setfill('0') << toBinary(S);

	string row = ss.str();
	for (int x = 1; x < xb.size(); x++)
		row.append(to_string(xb[x]));
	return row;
}

int MatrixInterpretator::nextStep(int S, vector<bool>& xb)
{
	string row = getRow(S, xb);

	stringstream ss;
	ss << setw(w.size()) << setfill('0') << toBinary(S);

	return toDec(changeA(ss.str(), row));
}

void MatrixInterpretator::v14Murav2(vector<bool> xb)
{
	int S = 0;

	while (!conditions[S])
	{
		conditions[S] = true;
		string row = getRow(S, xb);
		printState(S, row);
		S = nextStep(S, xb);
	}

	string row = getRow(S, xb);
	printState(S, row);

	if (S == 0)
		cout << "Алгортим завершил работу" << endl;
	else
		cout << "Алгоритм зациклился на состоянии " << S << endl;
}
