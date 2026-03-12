#pragma once
#include <iostream>
#include "TStack.h"
#include "Lexer.h"
#include "Syntaxer.h"


class Calc {

	string str;
	int res;
	vector<Token> postfix;
	vector<Token> infix;
	void doPostfix();
public:
	Calc() :res(0), str("") {
		postfix.clear();
		infix.clear();
	}
	Calc(string _in) {
		str = _in;
		res = 0;
		postfix.clear();
		infix.clear();
	}
	Calc(const Calc& calc) {
		str = calc.str;
		infix = calc.infix;
		postfix = calc.postfix;
		res = calc.res;
	}
	Calc& operator=(const Calc& calc) {
		if (this == &calc) return *this;
		str = calc.str;
		infix = calc.infix;
		postfix = calc.postfix;
		res = calc.res;
		return*this;
	}
	int Calculate();
	vector<Token> getInfix() {
		return infix;
	}
	vector<Token> getPostfix() {
		return postfix;
	}
	int getRes() {
		return res;
	}


};
