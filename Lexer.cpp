#include "Lexer.h"
#include <map>

using namespace lexer;

static const std::map<llvm::StringRef, lexer::Lexer::TokenType> tokens = {
        {llvm::StringRef("("), Lexer::TokenType::TOK_LEFT_PARENTHESIS},
        {llvm::StringRef(")"), Lexer::TokenType::TOK_RIGHT_PARENTHESIS},
        {llvm::StringRef("["), Lexer::TokenType::TOK_LEFT_BRACKET},
        {llvm::StringRef("]"), Lexer::TokenType::TOK_RIGHT_BRACKET},
        {llvm::StringRef("{"), Lexer::TokenType::TOK_LEFT_CURLY_BRACKET},
        {llvm::StringRef("}"), Lexer::TokenType::TOK_RIGHT_CURLY_BRACKET},
};

const Lexer::Token& Lexer::Lex() {
    SkipWhiteSpace();
    char *start = m_start;
    m_last_token.m_type = InternalLex();
    m_last_token.m_value = llvm::StringRef(start, m_start - start);
    return m_last_token;
}

void Lexer::SkipWhiteSpace() {
    while(*m_start == ' ' || *m_start == '\t')
        m_start++;
}

Lexer::TokenType Lexer::InternalLex() {
    if (m_start >= m_end)
        return TOK_EOF;
    /**
     *  ascii
     *     000 nul  001 soh  002 stx  003 etx  004 eot  005 enq  006 ack  007 bel
     *     010 bs   011 ht   012 nl   013 vt   014 np   015 cr   016 so   017 si
     *     020 dle  021 dc1  022 dc2  023 dc3  024 dc4  025 nak  026 syn  027 etb
     *     030 can  031 em   032 sub  033 esc  034 fs   035 gs   036 rs   037 us
     *     040 sp   041  !   042  "   043  #   044  $   045  %   046  &   047  '
     *     050  (   051  )   052  *   053  +   054  ,   055  -   056  .   057  /
     *     060  0   061  1   062  2   063  3   064  4   065  5   066  6   067  7
     *     070  8   071  9   072  :   073  ;   074  <   075  =   076  >   077  ?
     *     100  @   101  A   102  B   103  C   104  D   105  E   106  F   107  G
     *     110  H   111  I   112  J   113  K   114  L   115  M   116  N   117  O
     *     120  P   121  Q   122  R   123  S   124  T   125  U   126  V   127  W
     *     130  X   131  Y   132  Z   133  [   134  \   135  ]   136  ^   137  _
     *     140  `   141  a   142  b   143  c   144  d   145  e   146  f   147  g
     *     150  h   151  i   152  j   153  k   154  l   155  m   156  n   157  o
     *     160  p   161  q   162  r   163  s   164  t   165  u   166  v   167  w
     *     170  x   171  y   172  z   173  {   174  |   175  }   176  ~   177 del
     */
    switch (*m_start) {
        case '!':
        case '#'...'&':
        case '('...'/':
        case ':'...'@':
        case '['...'^':
        case '{'...'~':
        case '`':
            return DoOperator();
        case '"':
        case '\'':
            return DoStringLiteral();
        case '0'...'9':
            return DoNumberLiteral();
        case '_':
        case 'A'...'Z':
        case 'a'...'z':
            return DoIdentifier();
        default:
            return TOK_INVALID;
    }
}

Lexer::TokenType Lexer::DoOperator() {
    return GetKeyword(1);
}

Lexer::TokenType Lexer::GetKeyword(size_t size) {
    auto it = tokens.find(llvm::StringRef(m_start, size));
    if (it != tokens.end()) {
        m_start += size;
        return it->second;
    }
    return TOK_INVALID;
}

Lexer::TokenType Lexer::DoNumberLiteral() {
    while(IsDigit() || m_start == m_end) {
        m_start++;
    }
    return TOK_LIT_NUMBER;
}

Lexer::TokenType Lexer::DoIdentifier() {
    return TOK_INVALID;
}

Lexer::TokenType Lexer::DoStringLiteral() {
    m_start++;
    while (*m_start != '\"') {
        if (m_start == m_end)
            return TOK_INVALID;
        m_start++;
    }
    m_start++;
    return TOK_LIT_STRING;
}

bool Lexer::IsDigit() {
    switch(*m_start) {
        case '0'...'9': return true;
    }
    return false;
}
