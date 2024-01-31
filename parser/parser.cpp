#include "parser.hpp"

std::unordered_map<std::string, std::uint8_t> operator_precedences = {
    {"^", 6}, {"*", 5}, {"/", 5}, {"+", 4},   {"-", 4}, {"&", 3},
    {"|", 3}, {"<", 2}, {">", 2}, {"<=", 2}, {"=>", 2},{"==", 2}, {"!=", 2},
    {"and", 1}, {"or", 1}, {"=", 1}
};

Parser::Parser(Lexer& lexer) : lexer(lexer) {}

void Parser::parse_next() {
    AST ast;
    auto current = lexer.next();
    if (current.tokentype == Token::Type::OperatorDefinition) {
        auto precedence = lexer.next();
        if (precedence.tokentype != Token::Type::Base10) {
            std::cerr << "Expected a base 10 positive number, instead got " << precedence.lexeme << '\n';
            return;
        }
        auto name = lexer.next();
        if (name.tokentype != Token::Type::Operator) {
            std::cerr << "Expected an operator\n";
            return;
        }
        if (operator_precedences.find(name.lexeme) != operator_precedences.end()) {
            std::cerr << "Operator already exists you dumb piece of shit\n";
        }
        operator_precedences[name.lexeme] = std::stoi(precedence.lexeme);
        return;
    }
    lexer.rewind_token(current);
    parse_expression(0);
}

std::shared_ptr<Statement> Parser::parse_expression(int precedence) {
    auto& left = factor_token();
    logger.log_warning(static_cast<ValueNode*>(left.get())->value.lexeme);
    const auto& l = left;
    if (l->type == Statement::Type::Unexpected) {
        // segfaults here
        std::cout << "joe mama";
        auto e = static_cast<ValueNode*>(l.get());
        std::cerr << e->value.lexeme;
    }

    while (1) {
        Token op = lexer.next();
        int new_precedence = operator_precedences[op.lexeme];
        if (new_precedence == 0 || new_precedence <= precedence) {
            break;
        }
        auto right = parse_expression(new_precedence);
        auto binexpr = BinaryExpression {
                Statement::Type::BinaryExpr,
                left,
                right,
                op.lexeme,
                false
            };
        left = std::make_shared<BinaryExpression>(binexpr);
    }
    return left;
}

std::shared_ptr<Statement> Parser::factor_token() {
    ValueNode factor {Token {"", 0, 0, Token::Type::Unexpected}, Statement::Type::Unexpected};
    Token current = lexer.next();
    switch (current.tokentype)
    {
    case Token::Type::Base10:
        factor = ValueNode{current, Statement::Type::Value};
        break;
    default:
        factor = ValueNode{current, Statement::Type::Unexpected};
    }
    return std::make_shared<Statement>(factor);
}

// BinaryExpression Parser::parse_exp(int precedence) {
//     BinaryExpression bin;
//     auto left = std::make_shared<BinaryExpression>(factor());
//     while (1) {
//         auto op = lexer.next();
//         if (op.tokentype != Token::Type::Operator) {
//             std::cerr << "Expected a fuckign operator you dumbass\n";
//             break;
//         }
//         int new_precedence = operator_precedences[op.lexeme];
//         if (new_precedence == 0 || new_precedence <= precedence) {
//             break;
//         }
//         auto right = parse_exp(precedence);
//         // left = std::make_shared<BinaryExpression>();
//         std::cout << op.lexeme;
//     }
    
//     return bin;
// }

// BinaryExpression Parser::parse_expression() {
//     return parse_exp(5);
//     // left = factor();
//     // if (left.type == Statement::Type::Unexpected) {
//     //     std::cerr << "Bad left value\n";
//     //     return bin;
//     // }
//     // Token op = lexer.next();
//     // if (op.tokentype != Token::Type::Operator) {
//     //     std::cerr << "Expected an operator\n";
//     //     return bin;
//     // }
//     // right = factor();
//     // if (left.type == Statement::Type::Unexpected) {
//     //     std::cerr << "Bad left value\n";
//     //     return bin;
//     // }
//     // if (right.type == Statement::Type::Unexpected) {
//     //     std::cerr << "Bad right value\n";
//     //     return bin;
//     // }
// }

// BinaryExpression Parser::factor() {
//     Token current = lexer.next();
//     BinaryExpression val;
//     val.type = Statement::Type::Unexpected;
//     switch (current.tokentype) {
//     case Token::Type::Identifier:
//         val.type = Statement::Type::Variable;
//         break;
//     case Token::Type::Base10:
//         val.type = Statement::Type::Number;
//         break;
//     case Token::Type::Floating:
//         val.type = Statement::Type::Float;
//         break;
//     }
//     return val;
// }