#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "TStack.h"
#include "map"

class Syntaxer {

	vector<Token> in;
    vector<Token> fixedExpression;
	bool canPostfix;
    enum State { S0, S1, S2, S3, S4, S5, S6 };
    // “аблица переходов: [state][input] -> next_state
    // input: 0 = isNum true , 1 = false, 1 , 2 = false, 4 , 3 = false, 5, 4 = false, 0,2,3 
    State transitionTable[7][5] = {
        {S2, S1, S4, S6, S6},
        {S2, S6, S4, S6, S6},
        {S6, S3, S6, S5, S3},
        {S2, S6, S4, S6, S6},
        {S2, S1, S4, S6, S6},
        {S6, S3, S6, S5, S3},
        {S6, S6, S6, S6, S6}

    };
    State currentState = S0;
    
public:
    Syntaxer() {
        in.clear();
        canPostfix = true;
        currentState = S0;
        fixedExpression.clear();
    }
    Syntaxer(const vector<Token>& arr) {
        AnalyzeS(arr);
        if (canPostfix == false) {

            throw invalid_argument("can not fix an invalid Tokens vector (syntax problem)");
        }
    }
    Syntaxer(const Syntaxer& other) :
        in(other.in),
        currentState(other.currentState),
        canPostfix(other.canPostfix), 
        fixedExpression(other.fixedExpression){}

    Syntaxer& operator=(const Syntaxer& other) {
        if (this != &other) {
            in = other.in;
            currentState = other.currentState;
            canPostfix = other.canPostfix;
           
        }
        return *this;
    }

    // √лавный метод дл€ синтаксического анализа (нужен в конструкторе с вектором)
    void AnalyzeS(const vector<Token>& arr);



    void reset() {
        currentState = S0;
        in.clear();
        fixedExpression.clear();
        canPostfix = true;
    
    }

    bool isSyntApproved() const {
        return canPostfix;
    }

	const vector<Token>& getTokens() const {
		return in;
	}

    void printFixedInfix() {

        cout << "Infix:" << endl;
        for (size_t i = 0; i < in.size(); i++) {
            cout << " " << in[i].printToken();

        }
        cout << endl;
    }
    

    

private:
    void checkParenthesis();
    int getInputType(Token& token);
    void performAction(State from, State to, Token& token, size_t index);
    void handleUnaryMinus(Token& token);
    void handleOperand(Token& token);
    void handleBinaryOperator(Token& token);
    void handleOpenParenthesis(Token& token); 
    void handleCloseParenthesis(Token& token);
   
    void handleError(Token& token, size_t position);


};