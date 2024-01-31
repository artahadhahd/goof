#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>



int main() {
    while (1) {
        std::cout << "> ";
        std::string in;
        std::getline(std::cin, in);

        if (in == "exit")
            break;
        Lexer lexer(in);
        Parser parser(lexer);
        parser.parse_next();
    }
}