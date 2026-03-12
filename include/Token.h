#pragma once
#include<iostream>
#include <string>

using namespace std;

class Token {
	bool isNum;
	int val;

public:
	Token() :isNum(true), val(0) {}
	Token(bool _isNum, int _val) :isNum(_isNum), val(_val) {}
	Token(const Token& other) {
		isNum = other.isNum;
		val = other.val;
	}
	Token& operator=(const Token& other) {
		if (this == &other)return *this;

		isNum = other.isNum;
		val = other.val;
		return *this;
	}
	Token(const string& p) {
		if (p == "+") {
			val = 0;
			isNum = false;
		}
		else if (p == "-") {
			val = 1;
			isNum = false;
		}
		else if (p == "*") {
			val = 2;
			isNum = false;
		}
		else if (p == "/") {
			val = 3;
			isNum = false;
		}
		else if (p == "(") {
			val = 4;
			isNum = false;
		}
		else if (p == ")") {
			val = 5;
			isNum = false;
		}
		else {
			val = stoi(p);
			isNum = true;
		}
	}

	Token(const char& t) {
		isNum = false;
		val = -1;
		if (t == '*') {
			val = 2;
		}
		else if (t == ')') {
			val = 5;
		}
		else if (t == '(') {
			val = 4;
		}
		else if (t == '+') {
			val = 0;
		}
		else if (t == '-') {
			val = 1;
		}
		else if (t == '/') {
			val = 3;
		}
	}

	Token(int _val) {
		val = _val;
		isNum = true;
	}

	void setIsNum(bool puk) {
		this->isNum = puk;
	}
	void setVal(int vals) {
		this->val = vals;
	}
	bool isTokenNum() {
		return isNum;
	}
	int getVal() {
		return val;
	}
	string printToken() {
		if (isNum) {
			return to_string(val);
		}
		else if (!isNum && (val == 0)) {
			return "+";
		}
		else if (!isNum && (val == 1)) {
			return "-";
		}
		else if (!isNum && (val == 2)) {
			return "*";
		}
		else if (!isNum && (val == 3)) {
			return "/";
		}
		else if (!isNum && (val == 4)) {
			return "(";
		}
		else if (!isNum && (val == 5)) {
			return ")";
		}

	}
	int givePriority() {
		if (!isNum) {
			if (val == 0) return 1;
			if (val == 1) return 1;
			if (val == 2) return 2;
			if (val == 3) return 2;
		}
	}
};