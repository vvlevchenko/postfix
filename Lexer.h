
#ifndef LLVM_LEXER_H
#define LLVM_LEXER_H

#include <llvm/ADT/StringRef.h>

namespace lexer {
    class Lexer {
    public:
        Lexer(char *src): m_start(src), m_end(src + strlen(src)), m_last_token(TOK_INVALID, llvm::StringRef()){}

        enum TokenType {
            TOK_INVALID,
            TOK_EOF,
            TOK_LEFT_PARENTHESIS,
            TOK_RIGHT_PARENTHESIS,
            TOK_LEFT_BRACKET,
            TOK_RIGHT_BRACKET,
            TOK_LEFT_CURLY_BRACKET,
            TOK_RIGHT_CURLY_BRACKET,
            TOK_EOL
        };

        struct Token {
            Token(TokenType type, llvm::StringRef value):m_type(type),m_value(value){}
            TokenType m_type;
            llvm::StringRef m_value;
        };

        const Token& Lex();

    private:
        char *m_start;
        char *m_end;
        Token m_last_token;

        void SkipWhiteSpace();

        TokenType InternalLex();

        Lexer::TokenType DoOperator();

        Lexer::TokenType DoNumberLiteral();

        Lexer::TokenType DoIdentifier();

        Lexer::TokenType DoStringLiteral();
    };
}


#endif //LLVM_LEXER_H
