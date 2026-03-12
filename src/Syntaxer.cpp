#include "Syntaxer.h"
using namespace std;


void Syntaxer::AnalyzeS(const vector<Token>& arr) {
    reset();
    in = arr;
    fixedExpression.clear();

    // Сначала проверяем скобки
    checkParenthesis();
    if (!canPostfix) {
        return;
    }

    // Автомат для анализа и исправления выражения
    for (size_t i = 0; i < in.size(); i++) {
        Token& token = in[i];
        int inputType = getInputType(token);
        State previousState = currentState;

        // Выполняем переход
        currentState = transitionTable[currentState][inputType];

        // Если попали в ошибочное состояние
        if (currentState == S6) {
            handleError(token, i);
            return;
        }

        //  Действие по переходу, если все нормально
        performAction(previousState, currentState, token, i);
    }

  
    // Допустимые конечные состояния: S2, S5 (после операнда или закрывающей скобки)
    if (currentState != S2 && currentState != S5) {
        canPostfix = false;
        cerr << "Syntax error: expression ends with incomplete operation" << endl;
    }

    // Если анализ успешен, заменяем in на исправленное выражение
    if (canPostfix) {
        in = fixedExpression;
    }
}

int Syntaxer::getInputType(Token& token) {
    if (token.isTokenNum()) {
        return 0; // Операнд
    }
    else {
        int val = token.getVal();
        if (val == 1) {
            return 1; // Минус (может быть унарным или бинарным)
        }
        else if (val == 4) {
            return 2; // Открывающая скобка
        }
        else if (val == 5) {
            return 3; // Закрывающая скобка
        }
        else {
            return 4; // Другие операторы (+, *, /)
        }
    }
}


void Syntaxer::performAction(State from, State to, Token& token, size_t index) {
    // Обработка унарного минуса в начале или после '('
    if ((from == S0 && to ==S1) || (from == S4 && to == S1)) {
        handleUnaryMinus(token);
    }
    // Обработка обычного операнда
    else if ((from == S0 && to == S2)|| (from == S1 && to == S2)||(from == S3 && to == S2)||(from == S4 && to == S2)) {
        handleOperand(token);
    }
    // Обработка бинарного оператора
    else if ((from == S2 && to == S3) || (from == S5&& to==S3)) {
        handleBinaryOperator(token);
    }
    // Обработка открывающей скобки
    else if ((from == S0 || from == S1||from == S3||from == S4)&&(to==S4)) {
        handleOpenParenthesis(token);
    }
    // Обработка закрывающей скобки
    else if ((from == S2 || from == S5)&&(to==S5)) {
        handleCloseParenthesis(token);
    }
    
}

// Конкретные действия

void Syntaxer::handleUnaryMinus(Token& token) {
    // Добавляем ноль перед унарным минусом
    fixedExpression.push_back(Token(0));
    fixedExpression.push_back(token);
}


void Syntaxer::handleOperand(Token& token) {
    fixedExpression.push_back(token);
}

void Syntaxer::handleBinaryOperator(Token& token) {
    fixedExpression.push_back(token);
}

void Syntaxer::handleOpenParenthesis(Token& token) {
    fixedExpression.push_back(token);
}

void Syntaxer::handleCloseParenthesis(Token& token) {
    fixedExpression.push_back(token);
}


void Syntaxer::handleError(Token& token, size_t position) {
    canPostfix = false;
    cerr << "Syntax error at position " << position
        << ": unexpected token '" << token.printToken() << "'" << endl;
}




void Syntaxer::checkParenthesis() {
    TStack<int> stack(in.size());

    for (int i = 0;i<in.size();i++) {
        if (!in[i].isTokenNum()) {
            int val = in[i].getVal();
            if (val == 4) {
                stack.push(i);
            }
            else if (val == 5) {
                if (stack.isEmpty()) {
                    canPostfix = false;
                    cerr << "Syntax error: mismatched parentheses - extra closing parenthesis" << endl;
                    return;
                }
                stack.pop();
            }
        }
    }

    if (!stack.isEmpty()) {
        canPostfix = false;
        cerr << "Syntax error: mismatched parentheses - unclosed opening parenthesis" << endl;
    }
}