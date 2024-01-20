#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <unordered_map>



struct Node {
    enum class Type : char {
        BinaryExpression
    } nodetype;

    virtual long double interpret();
};

struct Variable {
    enum class Type : char {
        Int8,
        Int16,
        Int32,
        Int64,
        Single,
        Double
    } variabletype;
    bool is_signed = false;

    int scope;
    std::string name;
};

extern std::unordered_map<std::string, Variable> variable_pool {};

struct BinaryExpression: public Node {
    std::string op;
    struct Node *right = nullptr, *left = nullptr;

    long double interpret() override {

    }
};

enum class BranchType : char {
    Expression,
};

#endif