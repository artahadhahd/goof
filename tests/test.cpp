#include "../lexer/lexer.hpp"
#include "../parser/parser.hpp"
#include <catch2/catch_test_macros.hpp>

static std::string test_string = "# Hello! Here's a comment\nfunction fib(n) {fib(n);}";

TEST_CASE("Lexer divides correctly", "[lexer]") {
    Lexer lexer(test_string);
    std::vector<Token> all_tokens = lexer.get_all_tokens();

    SECTION ("Correct number of tokens (implying comments are ignored too)") {
        REQUIRE(all_tokens.size() == 12);
    }

    SECTION ("Tokens have the correct type") {
        REQUIRE (all_tokens[0].tokentype == Token::Type::Function);
        REQUIRE (all_tokens[1].tokentype == Token::Type::Identifier);
        REQUIRE (all_tokens[2].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[3].tokentype == Token::Type::Identifier);
        REQUIRE (all_tokens[4].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[5].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[6].tokentype == Token::Type::Identifier);
    }

    SECTION ("Tokens have the correct lexeme") {
        REQUIRE (all_tokens[0].lexeme == "function");
        REQUIRE (all_tokens[10].lexeme == ";");
        REQUIRE (all_tokens[11].lexeme == "}");
    }
}

// TEST_CASE ("Ast structure is all correct", "[AST]") {
//     SECTION ("AST test") {
//         AST ast;
//         BinaryExpression bin;
//         bin.type = Statement::Type::BinaryExpr;

//         auto var_ast = std::make_unique<AST>();
//         Variable var;
//         var.name = "hi";
//         var.refcnt = 1;
//         var.type = Statement::Type::Ident;
//         var_ast->statements.push_back(&var);

//         bin.left = std::move(var_ast);
//         bin.right = nullptr;
//         bin.op = "+";
//         ast.statements.push_back(&bin);
//         REQUIRE (ast.statements.size() == 1);
//         REQUIRE (static_cast<BinaryExpression*>(ast.statements.at(0))->op == "+");
//         REQUIRE (
//             static_cast<Variable*>(static_cast<BinaryExpression*>(ast.statements.at(0))->left->statements.at(0))->name == "hi"
//         );
//     }
// }