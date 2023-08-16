#include <iostream>
#include <cctype>

std::string toCamelCase(const std::string& input) {
    std::string output;
    bool newWord = true;

    for (char c : input) {
        if (std::isalpha(c)) {
            if (newWord) {
                output += std::toupper(c);
                newWord = false;
            } else {
                output += std::tolower(c);
            }
        } else if (std::isspace(c)) {
            newWord = true;
            output += c;
        }
    }

    return output;
}

int main() {
    std::string input = "conTenido oRIGINal";
    
    std::cout << "Texto: " << input << std::endl;

    std::string formatted = toCamelCase(input);

    std::cout << "Texto formateado en Camel Case: " << formatted << std::endl;

    return 0;
}
