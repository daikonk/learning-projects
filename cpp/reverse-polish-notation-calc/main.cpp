#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
#include <cctype>

using namespace std; 
class Stack {
    private:
        std::vector<int> data;

    public:

    void push(int val) {
        data.push_back(val);
    }

    int pop() {
        int res = data.back();
        data.pop_back();
        return res;
    }
};

std::vector<string> parse(string userInput) {
    std::vector<string> data;
    std::set<char> nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    std::set<char> ops = {'+', '-', '*', '/'};
    string numString;

    int numCount = 0;
    int opCount = 0;
    bool isValid = false;
    int p = 0;

    while (p < userInput.length()) {
        while (isspace(userInput[p])) {
            p += 1;
        }
        if (ops.find(userInput[p]) != ops.end() && (isspace(userInput[p + 1]) || p == userInput.length() - 1)) {

            numString.push_back(userInput[p]);
            p += 1;
            opCount += 1;

            if (opCount + 1 > numCount) {

                throw std::runtime_error("invalid input, got " + std::to_string(opCount) + " ops and " + std::to_string(numCount) + " nums, expected " + 
                                        std::to_string(numCount + 1) + " ops or " + std::to_string(opCount - 1) + " nums");

            }

        } else if (nums.find(userInput[p]) != nums.end()) {

            while (!isspace(userInput[p]) && p < userInput.length()) {

                if (!(nums.find(userInput[p]) != nums.end())) {
                    throw std::runtime_error("Invalid arg at position " + std::to_string(p) + " : " + userInput[p]);
                }

                numString.push_back(userInput[p]);
                p += 1;

            }

            numCount += 1;

        } else {

            throw std::runtime_error("Invalid arg at position " + std::to_string(p) + " : " + userInput[p]);

        }

        data.push_back(numString);
        numString = "";

    }

    if (opCount + 1 != numCount) {
        throw std::runtime_error("invalid input, got " + std::to_string(opCount) + " ops and " + std::to_string(numCount) + " nums, expected " + 
                                 std::to_string(numCount + 1) + " ops or " + std::to_string(opCount - 1) + " nums");
    }

    return data;
}

int evaluate(std::vector<string> data) {
    Stack stack;
    std::set<string> ops = {"+", "-", "*", "/"};
    int val;

    for (string token : data) {

        switch (token.at(0)) {
            case '+':
                stack.push(stack.pop() + stack.pop());
                break;
            case '*':
                stack.push(stack.pop() * stack.pop());
                break;
            case '-':
                val = stack.pop();
                stack.push(stack.pop() - val);
                break;
            case '/':
                val = stack.pop();
                stack.push(stack.pop() / val);
                break;
            default:
                stack.push(std::stoi(token));
        }
    }

    return stack.pop();

}

int main() {
    int res;

    while (1) {
        string userInput;
        cout << "Write your reverse polish notation to be calculated..\n"; getline(cin, userInput);

        try {

            std::vector<string> valArr = parse(userInput);
            cout << evaluate(valArr) << endl;

        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << endl;
        }

    }

    return 0;
}
