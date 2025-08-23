#include <iostream>
using namespace std;

// enum State {
//     DIGIT,
//     EQUALS,
//     PLUS,
//     MINUS,
// };

// void switchState(const State& newState) {
//     currentState = newState;
// }

// State currentState;
struct BaseState {
    char currentChar;
    virtual ~BaseState() = default;
    virtual void handle() = 0;
    virtual void switchState(char ch) = 0;
};

struct DigitState : BaseState {
    void handle() override {
        cout << "Handling digit state" << endl;
    }
    
    void switchState(char ch) override {
        if (isdigit(ch)) {
            cout << "Staying in Digit State" << endl;
        } else {
            cout << "Invalid input, staying in Digit State" << endl;
        }
    }
};

struct EqualsState : BaseState {
    void handle() override {
        cout << "Handling equals state" << endl;
    }
    
    void switchState(char ch) override {
        if (ch == '=') {
            cout << "Staying in Equals State" << endl;
        } else {
            cout << "Invalid input, staying in Equals State" << endl;
        }
    }
};

struct PlusState : BaseState {
    void handle() override {
        cout << "Handling plus state" << endl;
    }
    
    void switchState(char ch) override {
        if (ch == '+') {
            cout << "Staying in Plus State" << endl;
        } else {
            cout << "Invalid input, staying in Plus State" << endl;
        }
    }
};

struct MinusState : BaseState {
    void handle() override {
        cout << "Handling minus state" << endl;
    }
    
    void switchState(char ch) override {
        if (ch == '-') {
            cout << "Staying in Minus State" << endl;
        } else {
            cout << "Invalid input, staying in Minus State" << endl;
        }
    }
};


void application() {
    BaseState* currentState = nullptr;
    string input = "123 + 456 == 789 - 0";
    
    for (char ch : input) {
        if (isspace(ch)) {
            continue; // Skip spaces
        } else if (isdigit(ch)) {
            if (!currentState || dynamic_cast<DigitState*>(currentState) == nullptr) {
                delete currentState;
                currentState = new DigitState();
            }
        } else if (ch == '=') {
            if (!currentState || dynamic_cast<EqualsState*>(currentState) == nullptr) {
                delete currentState;
                currentState = new EqualsState();
            }
        } else if (ch == '+') {
            if (!currentState || dynamic_cast<PlusState*>(currentState) == nullptr) {
                delete currentState;
                currentState = new PlusState();
            }
        } else if (ch == '-') {
            if (!currentState || dynamic_cast<MinusState*>(currentState) == nullptr) {
                delete currentState;
                currentState = new MinusState();
            }
        } else {
            cout << "Lexical Error reading character \"" << ch << "\"" << endl;
            continue;
        }
        
        if (currentState) {
            currentState->handle();
            currentState->switchState(ch);
        }
    }
    
    delete currentState;
}

int main() {
    application();
    return 0;
}