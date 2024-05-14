#include <iostream>
#include <string>

enum class State { INIT, INT, WORD, STRING, ERROR, DECIMAL_POINT, FRACTION };

void tokenize(std::string& inputString) {
    State state = State::INIT;
    std::string lexeme = "";
    bool contin = true;
    int index = 0;
    while (contin) {
        char c;
        if (index < inputString.size()) {
            c = inputString[index];
        }
        else {
            c = -1;
        }
        std::cerr << "state = " << static_cast<int>(state)
            << ", index = " << index
            << ", c = '" << c
            << "', lexeme = '" << lexeme
            << "'\n";
        switch (state) {
        case State::INIT:
            if (c >= '0' && c <= '9') {
                state = State::INT;
                lexeme += c; // start building the integer lexeme
            }
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                state = State::WORD;
                lexeme += c; // start building the word lexeme
            }
            else if (c == '"') {
                state = State::STRING;
            }
            else if (c == ' ') {
                // Ignore spaces
            }
            else if (c == -1) {
                contin = false;
            }
            else {
                std::cerr << "State::INIT going to ERROR\n";
                state = State::ERROR;
            }
            break;
        case State::INT:
            if (c >= '0' && c <= '9') {
                lexeme += c;
            }
            else if (c == '.') {
                lexeme += c;
                state = State::DECIMAL_POINT;
            }
            else {
                std::cout << "Found integer '" << lexeme << "'\n";
                lexeme = "";
                state = State::INIT;
                index--;
            }
            break;
        case State::WORD:
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                lexeme += c;
            }
            else {
                std::cout << "Found word '" << lexeme << "'\n";
                lexeme = "";
                state = State::INIT;
                index--;
            }
            break;
        case State::STRING:
            if (c == '"') {
                std::cout << "Found string '" << lexeme << "'\n";
                lexeme = "";
                state = State::INIT;
            }
            else if (c == -1) {
                state = State::ERROR;
            }
            else {
                lexeme += c;
            }
            break;
        case State::DECIMAL_POINT:
            if (c >= '0' && c <= '9') {
                lexeme += c;
                state = State::FRACTION;
            }
            else {
                std::cerr << "Digit expected following decimal point\n";
                state = State::ERROR;
            }
            break;
        case State::FRACTION:
            if (c >= '0' && c <= '9') {
                lexeme += c;
            }
            else {
                std::cout << "Found float '" << lexeme << "'\n";
                lexeme = "";
                state = State::INIT;
                index--;
            }
            break;
        case State::ERROR:
            std::cerr << "Error: character '" << c << "' found at index " << index << "\n";
            contin = false;
            break;
        }
        if (state == State::INIT && c == -1) {
            contin = false;
        }
        index++;
    }
}

int main() {
    std::string line;
    getline(std::cin, line);
    tokenize(line);
}
