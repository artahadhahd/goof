#include "lexer.hpp"

Lexer::Lexer(std::string &input_) : input(input_), buffer_size(input.size()) {}

Token Lexer::next() {
    if (!has_next()) {
        return Token{"", line, cursor, Token::Type::End};
    }
    std::string lexeme;
    bool breaking = false;
    switch (input[cursor]) {
    case '"':
        while (has_next()) {
            lexeme += input[cursor];
            ++cursor;
            if (input[cursor] == '"' && !breaking) {
                break;
            }
            if (input[cursor] == '\\' && !breaking) {
                breaking = true;
            } else {
                breaking = false;
            }
        }
        if (!has_next()) {
            return Token{lexeme, line, cursor, Token::Type::UnterminatedString};
        }
        lexeme += input[cursor++];
        return Token{lexeme, line, cursor, Token::Type::String};
    case '#':
        while (has_next() && input[cursor] != '\n') {
            ++cursor;
        }
        return next();
    case '\n':
        ++line;
        ++cursor;
        return next();
    case '\t':
    case ' ':
        while (has_next() && input[cursor] == ' ') {
            ++cursor;
        }
        return next();
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case '@':
    case '~':
    case '&':
    case '|':
    case '^':
    case '!':
    case '.':
        ++cursor;
        return Token{std::string{input[cursor - 1]}, line, cursor,
                     Token::Type::Operator};
    case ';':
        ++cursor;
        return Token{";", line, cursor, Token::Type::EndOfInstruction};
    case '0':
        lexeme += input[cursor];
        ++cursor;
        if (!has_next()) {
            return Token{lexeme, line, cursor, Token::Type::Base10};
        }
        if (input[cursor] == '#') {
            do {
                lexeme += input[cursor];
                ++cursor;
            } while (has_next() && (isalnum(input[cursor]) || input[cursor] == '_'));
            return Token{lexeme, line, cursor, Token::Type::AnyBase};
        }
        if (input[cursor] == '.') {
            do {
                lexeme += input[cursor];
                ++cursor;
            } while (has_next() && isdigit(input[cursor]));
            return Token{lexeme, line, cursor, Token::Type::Floating};
        }
    }
    if (isalpha(input[cursor]) || input[cursor] == '_') {
        while (has_next() && (isalnum(input[cursor]) || input[cursor] == '_')) {
            lexeme += input[cursor];
            ++cursor;
        }
        if (lexeme == "for")
            return Token{lexeme, line, cursor, Token::Type::For};
        if (lexeme == "while")
            return Token{lexeme, line, cursor, Token::Type::While};
        if (lexeme == "struct")
            return Token{lexeme, line, cursor, Token::Type::Struct};
        if (lexeme == "if")
            return Token{lexeme, line, cursor, Token::Type::If};
        if (lexeme == "else")
            return Token{lexeme, line, cursor, Token::Type::Else};
        if (lexeme == "proc")
            return Token{lexeme, line, cursor, Token::Type::Proc};
        return Token{lexeme, line, cursor, Token::Type::Identifier};
    }
    if (isdigit(input[cursor])) {
        while (has_next() && isdigit(input[cursor])) {
            lexeme += input[cursor];
            ++cursor;
        }
        if (!has_next() || input[cursor] != '.') {
            return Token{lexeme, line, cursor, Token::Type::Base10};
        }
        do {
            lexeme += input[cursor];
            ++cursor;
        } while (has_next() && isdigit(input[cursor]));
        return Token{lexeme, line, cursor, Token::Type::Floating};
    }
    return Token{std::string{input[cursor]}, line, cursor, Token::Type::Unexpected};
}

std::vector<Token> Lexer::get_all_tokens() {
    std::vector<Token> out;
    while (has_next()) {
        out.push_back(next());
    }
    return out;
}

bool Lexer::has_next() const noexcept { return cursor < buffer_size; }