
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
            TOK_LIT_NUMBER,
            TOK_LIT_STRING,
            TOK_LIT_BOOL_TRUE,
            TOK_LIT_BOOL_FALSE,
            TOK_IDENTIFIER,
            TOK_OP_PLUS,
            TOK_OP_MINUS,
            TOK_OP_DIV,
            TOK_OP_MUL,
            TOK_OP_MOD,
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

        Lexer::TokenType GetKeyword(const char *start, size_t size);

        bool IsEnd() const;

        bool IsLexem() const;
    };
}


#endif //LLVM_LEXER_H
