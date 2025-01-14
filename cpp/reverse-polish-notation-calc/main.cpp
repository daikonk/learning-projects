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
    int p = 0;

    while (p < userInput.length()) {
        while (isspace(userInput[p])) {
            p += 1;
        }
        if (ops.find(userInput[p]) != ops.end() && (isspace(userInput[p + 1]) || p == userInput.length() - 1)) {

            numString.push_back(userInput[p]);
            p += 1;
            opCount += 1;

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
        throw std::runtime_error("Invalid input, got " + std::to_string(opCount) + " OPS and " + std::to_string(numCount) + " NUMS, expected " + 
                                 std::to_string(numCount + 1) + " OPS or " + std::to_string(opCount - 1) + " NUMS");
    }

    return data;
}

int main() {
    Stack stack;

    while (1) {
        string userInput;
        cout << "Write your reverse polish notation to be calculated..\n"; getline(cin, userInput);

        try {
            auto valArr = parse(userInput);
            for (auto c : valArr) {
                cout << c << " ";
            }
            cout << endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << endl;
        }

    }

    return 0;
}
