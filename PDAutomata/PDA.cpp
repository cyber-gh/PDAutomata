#include "PDA.h"



void PDA::readMachine(string filename){
	ifstream fin(filename);
	int nr;
	fin >> nr;

	
	nrStates = 0;
	for (int index; nr--; nrStates++) {
		fin >> index;
		states.push_back(index);
	}

	fin >> nr;
	nrAlphabet = 0;
	for (char c; nr--; nrAlphabet++) {
		fin >> c;
		alphabet.insert(c);
	}

	fin >> nr;
	beginState = nr;
	fin >> nr;
	for (int index; nr--; ) {
		fin >> index;
		finalStates.push_back(index);

	}

	fin >> nr;
	nrTrans = 0;
	for (; nr--; nrTrans++) {
		int from, to;
		char topOfStack;
		string pushToStack;
		char dummy;
		char letter;
		fin >> from >> to >> letter >> topOfStack >> dummy >> pushToStack;
		reverse(pushToStack.begin(), pushToStack.end());
		Transitions[from].push_back({ to, letter, topOfStack, pushToStack });
	}
}

PDA::PDA(string filename){
	readMachine(filename);
}


PDA::~PDA()
{
}

bool PDA::checkWord(string word){
	reverse(word.begin(), word.end());
	struct local {
		int state;
		stack<char> st;
		string word;
	};

	stack<local> ST;

	local tmp = { beginState, getEmptyStack(), word };
	ST.push(tmp);
	while (!ST.empty()) {
		local curr = ST.top();
		{
			cout << curr.state << " " << curr.word << " ";
			stack<char> tmp = curr.st;
			while (!tmp.empty()) {
				cout << tmp.top();
				tmp.pop();
			}
			cout << endl;
		}
		
		ST.pop();

		if (curr.st.empty() && curr.word.empty() && isFinal(curr.state)) {
			return true;
		}
		if (curr.st.empty()) continue;
		for (auto it : Transitions[curr.state]) {
			if (!curr.word.empty()) {
				if (curr.word.back() == it.letter && curr.st.top() == it.topOfStack) {
					string newWord = curr.word;
					newWord.pop_back();
					stack<char> newStack = curr.st;
					newStack.pop();
					for (auto it2 : it.pushToStack) {
						if (it2 == LAMBDA) continue;
						newStack.push(it2);
					}
					ST.push({ it.state, newStack, newWord });
				}
			}
			if (curr.word.empty() && it.letter == LAMBDA && curr.st.top() == it.topOfStack) {
				stack<char> newStack = curr.st;
				newStack.pop();
				for (auto it2 : it.pushToStack) {
					if (it2 == LAMBDA) continue;
					newStack.push(it2);
				}
				ST.push({ it.state, newStack, curr.word });
			}
		}
	}
	return false;
}


bool PDA::isFinal(int state){
	for (auto it : finalStates) if (state == it) return true;
	return false;
}
stack<char> PDA::getEmptyStack() {
	stack<char> rs;
	rs.push('Z');
	return rs;
}