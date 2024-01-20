#include "../lexer/lexer.hpp"
#include <catch2/catch_test_macros.hpp>

static std::string test_string = "# Hello! Here's a comment\nproc fib(n) {fib(n);}";

TEST_CASE("Lexer divides correctly", "[lexer]") {
    Lexer lexer(test_string);
    std::vector<Token> all_tokens = lexer.get_all_tokens();

    SECTION ("Correct number of tokens (implying comments are ignored too)") {
        REQUIRE(all_tokens.size() == 12);
    }

    SECTION ("Tokens have the correct type") {
        REQUIRE (all_tokens[0].tokentype == Token::Type::Proc);
        REQUIRE (all_tokens[1].tokentype == Token::Type::Identifier);
        REQUIRE (all_tokens[2].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[3].tokentype == Token::Type::Identifier);
        REQUIRE (all_tokens[4].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[5].tokentype == Token::Type::Operator);
        REQUIRE (all_tokens[6].tokentype == Token::Type::Identifier);
    }

    SECTION ("Tokens have the correct lexeme") {
        REQUIRE (all_tokens[0].lexeme == "proc");
        REQUIRE (all_tokens[10].lexeme == ";");
        REQUIRE (all_tokens[11].lexeme == "}");
    }
}

TEST_CASE ("Parser works correctly", "[parser]") {
    
}