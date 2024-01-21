#ifndef PARSER_HPP
#define PARSER_HPP
#include "../lexer/lexer.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

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

struct Statement {
    enum class Type {
        BinaryExpr,
        Ident,
        Variable,
        FunctionCall,
    } type;
};

struct AST {
    std::vector<Statement*> statements;
};

struct ValueNode {
    Token value;
};

struct BinaryExpression : public Statement {
    std::unique_ptr<AST> left, right;
    std::string op;
    bool user_defined;
};

struct Variable : public Statement {
    std::string name;
    size_t refcnt;
    ValueNode value;
};

struct FunctionCall : public Statement {
    std::string function_name;
    std::vector<ValueNode*> arguments;
};

class Parser {
    Lexer lexer;
    public:
    Parser(std::string& input);
    Parser(const Lexer lexer);
    void parse_next();
    private:
    BinaryExpression parse_expression();
};
#endif