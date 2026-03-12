#pragma once
#include <iostream>
#include "Token.h"
#include <vector>

using namespace std;

class Lexer {
    vector<Token> arr;
    enum State { S0, S1, S2, S3,S4 };
    // “аблица переходов: [state][input] -> next_state
    // input: 0 = 0 , 1 = 1..9 , 2 = digit oper, 3 = any else 
    State transitionTable[5][4] = {
        {S2, S1, S3, S4},
        {S1, S1, S3, S4},
        {S4, S4, S3, S4},
        {S2, S1, S3, S4},
        {S4, S4, S4, S4}

    };
    State currentState = S0;
    bool LexicallyAppropriate = true;
    string currentNumber;
public:
    Lexer() {
        currentState = S0;
        arr.clear();
        LexicallyAppropriate = true;
        currentNumber.clear();
    }
    Lexer(const string& expression) {
        Analyze(expression);
        if (LexicallyAppropriate == false) {

            throw invalid_argument("Can not initialize an invalid expression (lexical problem)");
        }
    }
    Lexer(const Lexer& other) :
        arr(other.arr),
        currentState(other.currentState),
        LexicallyAppropriate(other.LexicallyAppropriate),
        currentNumber(other.currentNumber) {}



    Lexer& operator=(const Lexer& other) {
        if (this != &other) {
            arr = other.arr;
            currentState = other.currentState;
            LexicallyAppropriate = other.LexicallyAppropriate;
            currentNumber = other.currentNumber;
        }
        return *this;
    }

    // √лавный метод дл€ лексического анализа (нужен в конструкторе со строкой)
    void Analyze(const string& expression);


   
    void reset() {
        currentState = S0;
        currentNumber.clear();
        LexicallyAppropriate = true;
        arr.clear();
    }

    bool isLexicallyApproved() const {
        return LexicallyAppropriate;
    }

    const vector<Token>& getTokens() const{
        return arr;
    }

    void printTokens() {
       
        cout << "Tokens:" << endl;
        for (size_t i = 0; i < arr.size(); i++) {
            cout << " " << arr[i].printToken();
             
        }
        cout << endl;
    }


private:
    //это все штуки типо функции дл€ исполнени€ при переходе из состо€ни€ в состо€ние(ну чтобы не только провер€ть, но и токенизировать сразу)
    void processChar(char c, size_t position);
    int getInputType(char c) const;
    void performAction(State from, State to, char c, size_t position);
    void startNumber(char c);
    void continueNumber(char c);
    void handleZeroAsNumber(char c);
    void finishNumberBeforeOperator(char c);
    void handleOperatorAfterOperator(char c);
    void handleOperatorAtStart(char c);
    void finishNumber();
    void handleError(char c, size_t position);
};


