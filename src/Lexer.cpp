#include "Lexer.h"

void Lexer::Analyze(const string& expression){
    reset();

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        processChar(c, i);

        if (currentState == S4) {
            LexicallyAppropriate = false;
            arr.clear();
            return;
        }
    }

    // Если в конце есть несобранное число, добавляем его
    if (!currentNumber.empty()) {
        finishNumber();
    }
}


// Обработка одного символа с действиями
void Lexer::processChar(char c, size_t position) {
    int inputType = getInputType(c);
    State previousState = currentState;

    //переход
    currentState = transitionTable[currentState][inputType];

    // Выполняем действия, связанные с переходом
    performAction(previousState, currentState, c, position);

    // Проверяем, не попали ли в ошибочное состояние
    if (currentState == S4) {
        handleError(c, position);
    }
}

// Определение типа входного символа
int Lexer::getInputType(char c) const {
    if (isdigit(static_cast<unsigned char>(c))) {
        if (c == '0') {
            return 0; 
        }
        else {
            return 1; 
        }
    }
    else if (c == '+' || c == '-' || c == '/' ||
        c == '*' || c == '(' || c == ')') {
        return 2; 
    }
    else {
        return 3; 
    }
}

// Выполнение действий при переходе между состояниями
void Lexer::performAction(State from, State to, char c, size_t position) {
    // Начало сбора числа (S0 -> S1 или S3 -> S1)
    if ((from == S0 && to == S1) || (from == S3 && to == S1)) {
        startNumber(c);
    }

    // Продолжение сбора числа (S1 -> S1)
    else if (from == S1 && to == S1) {
        continueNumber(c);
    }

    // Встретили '0' как отдельное число (S0 -> S2 или S3 -> S2)
    else if ((from == S0 && to == S2) || (from == S3 && to == S2)) {
        handleZeroAsNumber(c);
    }

    // Встретили оператор, когда собирали число (S1 -> S3 или S2 -> S3)
    else if ((from == S1 && to == S3) || (from == S2 && to == S3)) {
        finishNumberBeforeOperator(c);
    }

    // Встретили оператор после оператора (S3 -> S3)
    else if (from == S3 && to == S3) {
        handleOperatorAfterOperator(c);
    }

    // Встретили оператор (S0 -> S3)
    else if (from == S0 && to == S3) {
        handleOperatorAtStart(c);
    }
}

// действия автомата

void Lexer::startNumber(char c) {
    currentNumber = c; 
}

void Lexer::continueNumber(char c) {
    currentNumber += c;
}

void Lexer::handleZeroAsNumber(char c) {
    // '0' как отдельное число
    arr.push_back(Token(0));
    
}

void Lexer::finishNumberBeforeOperator(char c) {
    // Завершаем сбор числа перед оператором
    if (!currentNumber.empty()) {
        try {
            int value = stoi(currentNumber);
            arr.push_back(Token(value));
            currentNumber.clear();
        }
        catch (const exception& e) {
            currentState = S4;
            LexicallyAppropriate = false;
            return;
        }
    }
    // Токеним оператор
    arr.push_back(Token(c));
}

void Lexer::handleOperatorAfterOperator(char c) {
    //просто закидываем (можно было объединить с функцией ниже но я заленилась))
    arr.push_back(Token(c));
}

void Lexer::handleOperatorAtStart(char c) {
    // Оператор в начале выражения (возможно унарный)
    arr.push_back(Token(c));
}

void Lexer::finishNumber() {
    // Завершение сбора числа в конце строки
    if (!currentNumber.empty()) {
        try {
            int value = stoi(currentNumber);
            arr.push_back(Token(value));
            currentNumber.clear();
        }
        catch (const exception& e) {
            currentState = S4;
            LexicallyAppropriate = false;
        }
    }
}

void Lexer::handleError(char c, size_t position) {
    LexicallyAppropriate = false;
    cerr << "Caught lexical error at position " << position
        << ": invalid character '" << c << "'" << endl;
}
