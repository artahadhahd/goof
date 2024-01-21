#ifndef PARSER_HPP
#define PARSER_HPP
#include "../lexer/lexer.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// struct Object {
//     size_t refcount;
// };

// struct Node {
//     enum class Type : char {
//         BinaryExpression
//     } nodetype;

//     virtual Object interpret();
// };

// struct Variable {
//     enum class Type : char {
//         Int8, 
//         Int16,
//         Int32,
//         Int64,
//         Single,
//         Double
//     } variabletype;
//     bool is_signed = false;

//     int scope;
//     std::string name;
// };

// extern std::unordered_map<std::string, Variable> variable_pool {};

// struct BinaryExpression: public Node {
//     std::string op;
//     struct Node *right = nullptr, *left = nullptr;

//     Object interpret() override {

//     }
// };

// enum class BranchType : char {
//     Expression,
// };

struct Statement {
    enum class Type {
        BinaryExpr,
        Ident
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
};

struct Variable : public Statement {
    std::string name;
    size_t refcnt;
    ValueNode value;
};

#endif