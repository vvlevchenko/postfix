#include <llvm/Support/raw_ostream.h>
#include <iostream>
#include "Lexer.h"

using lexer::Lexer;

int
main() {
    char c[1024];
    std::string text;
    llvm::raw_string_ostream ostream(text);
    while (std::cin >> c) {
        std::cout << ">>" << c;
        ostream << c;
    }
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
            case Lexer::TokenType::TOK_EOF:
                return 0;
            default:
                std::cout << "Unknown token: " << t.m_value.str() << std::endl;
                return 1;

        }
    }
}