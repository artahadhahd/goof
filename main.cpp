#include "lexer/lexer.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::uint8_t> operator_precedences = {
    {"^", 5}, {"*", 4}, {"/", 4}, {"+", 3},   {"-", 3}, {"&", 2},
    {"|", 2}, {"<", 1}, {">", 1}, {"and", 0}, {"or", 0}};

/**
 * UNARY OPERATORS:
 * ~, -, !, +, @, $
 *
 * BINARY OPERATORS:
 * Highest precedence: ^
 * then: * /
 * then: + - & |
 * then: < > >= <=
 * and lastly: && ||
 */

struct AstNode {};

class Parser {
    Lexer lexer;
    uint32_t scope = 0;

  public:
    Parser(std::string &in) : lexer(in) {}
    Parser(Lexer lexer_) : lexer(lexer_) {}

    AstNode assignment() {
        // auto current_token = lexer.next();
        // if (current_token.tokentype == Token::Type::Identifier) {
        //     VariableNode node;
        //     node.name = current_token.lexeme;
        //     node.scope = scope;
        //     current_token = lexer.next();
        //     if (current_token.lexeme != "=") {
        //         node.iserror = true;
        //         node.error = "Expected an assignment";
        //         return node;
        //     }
        //     return node;
        // }
        // return AstNode {};
    }
};

int main() {
    while (1) {
        std::cout << "> ";
        std::string in;
        std::getline(std::cin, in);

        if (in == "exit")
            break;

        Lexer lexer(in);
        Token next = lexer.next();
        while (next.tokentype != Token::Type::End) {
            if (next.tokentype == Token::Type::Unexpected) {
                printf("Unexpected %s\n", next.lexeme.c_str());
                break;
            }
            if (next.tokentype == Token::Type::UnterminatedString) {
                printf("Unterminated string literal: %s\n", next.lexeme.c_str());
                break;
            }
            std::cout << next.lexeme << " has " << (int)next.tokentype << '\n';
            next = lexer.next();
        }
    }
}