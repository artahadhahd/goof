#ifndef PARSER_HPP
#define PARSER_HPP
#include "../lexer/lexer.hpp"
#include "../logging/logging.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>

extern std::unordered_map<std::string, std::uint8_t> operator_precedences;

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
        Unexpected,
        Value,
        BinaryExpr,
        Ident,
        Variable,
        FunctionCall,
        Number,
        Float
    } type;
};

struct AST {
    std::vector<Statement*> statements;
};

struct ValueNode : public Statement {
    ValueNode(Token v, Statement::Type t) : value(v) {
        this->type = t;
    }
    Token value;
};

struct BinaryExpression : public Statement {
    BinaryExpression(Statement::Type t, std::shared_ptr<Statement> l, std::shared_ptr<Statement> r, std::string op, bool u) {
        type = t;
        left = l;
        right = r;
        user_defined = u;
    }
    std::shared_ptr<Statement> left, right;
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
    Lexer& lexer;
    public:
    Parser(const std::string input);
    Parser(Lexer& lexer);
    void parse_next();
    private:
    std::shared_ptr<Statement> parse_expression(int);
    // BinaryExpression parse_exp(int);
    std::shared_ptr<Statement> factor_token();
    protected:
    friend class Logger;
    Logger logger;
};
#endif