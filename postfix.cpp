#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include "Lexer.h"

using lexer::Lexer;

int
main() {

    std::string text, line;
    llvm::raw_string_ostream ostream(text);
    while (std::getline(std::cin, line))
        ostream << line << '\n';

    std::cout << std::endl;
    std::cout << "in: '" << ostream.str() << "'" << std::endl;
    Lexer lex((char *) ostream.str().c_str());
    while(true) {
        const Lexer::Token& t = lex.Lex();
        switch (t.m_type) {
            case Lexer::TokenType::TOK_INVALID:
                std::cout << "Unsupported token: " << t.m_value.str() << std::endl;
                return 1;
            case Lexer::TokenType::TOK_LEFT_PARENTHESIS:
                std::cout << "( -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_RIGHT_PARENTHESIS:
                std::cout << ") -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LEFT_BRACKET:
                std::cout << "[ -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_RIGHT_BRACKET:
                std::cout << "] -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LEFT_CURLY_BRACKET:
                std::cout << "{ -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_RIGHT_CURLY_BRACKET:
                std::cout << "} -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LIT_NUMBER:
                std::cout << "number: -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LIT_STRING:
                std::cout << "string: -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LIT_BOOL_FALSE:
                std::cout << "bool: -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_LIT_BOOL_TRUE:
                std::cout << "bool: -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_IDENTIFIER:
                std::cout << "identifier: -> " << t.m_value.str() << std::endl;
                break;
            case Lexer::TokenType::TOK_EOF:
                return 0;
            default:
                std::cout << "Unknown token: "<< std::to_string(t.m_type) << t.m_value.str() << std::endl;
                return 1;

        }
    }
}