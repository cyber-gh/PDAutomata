#pragma once

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

const char LAMBDA = '~';

struct trans {
	int state;
	char letter;
	char topOfStack;
	string pushToStack;
};

class PDA{
	vector<int> states;
	vector<int> finalStates;
	int beginState;
	set<char> alphabet;
	unordered_map<int, vector<trans> > Transitions;
	int nrTrans;
	int nrStates;
	int nrAlphabet;
	bool isFinal(int state);

	stack<char> getEmptyStack();

	void readMachine(string filename);

public:
	PDA(string filename);
	~PDA();

	bool checkWord(string );
};

