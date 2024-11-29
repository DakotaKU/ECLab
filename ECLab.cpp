#include <iostream>
#include <iomanip> // For fixed and setprecision
#include <string>
using namespace std;

// Function to extract a double-precision number from a string
double extractNumeric(const string& str) {
    // Length validation
    if (str.length() == 0 || str.length() > 20) {
        return -999999.99;
    }

    // Initialize flags
    bool hasDecimal = false;
    bool hasSign = false;
    bool isValid = true;

    size_t i = 0;

    // Check for leading sign
    if (str[i] == '+' || str[i] == '-') {
        hasSign = true;
        i++;
    }

    // Process remaining characters
    for (; i < str.length(); ++i) {
        char c = str[i];

        if (c == '.') {
            if (hasDecimal) { // Second decimal point invalidates input
                isValid = false;
                break;
            }
            hasDecimal = true;
        } else if (!isdigit(c)) { // Non-digit character invalidates input
            isValid = false;
            break;
        }
    }

    // If invalid, return special error value
    if (!isValid || i == (hasSign ? 1 : 0)) {
        return -999999.99;
    }

    // Convert valid string to double manually
    try {
        double value = stod(str); // std::stod is acceptable for conversion
        return value;
    } catch (...) {
        return -999999.99; // Catch any conversion error
    }
}

int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4)
                 << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
