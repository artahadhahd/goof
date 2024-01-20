#ifndef LEXER_HPP
#define LEXER_HPP
#include <cstdint>
#include <string>
#include <vector>

struct Token {
    std::string lexeme;
    std::size_t line, pos;
    enum class Type : std::int8_t {
        UnterminatedString = -3,
        Unexpected = -2,
        End = -1,
        Identifier = 0,
        Base10,
        AnyBase,
        Operator,
        Floating,
        String,
        EndOfInstruction,

        // keywords
        If,
        Else,
        For,
        While,
        Struct,
        Proc
    } tokentype;
};

class Lexer {
    std::string &input;
    std::size_t cursor = 0, line = 1, buffer_size;

  public:
    explicit Lexer(std::string &input_);
    Token next();
    std::vector<Token> get_all_tokens();

  private:
    bool has_next() const noexcept;
};
#endif