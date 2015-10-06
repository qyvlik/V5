#ifndef TOKEN_H
#define TOKEN_H

#include <cassert>
#include <string>
#include <list>

namespace V5 {

#define TOKEN_LIST(T, K)                                               \
    T(ERROR, "ERROR",0)                                                \
    /* End of source indicator. */                                     \
    T(EOS, "EOS", 0)                                                   \
    \
    /* Punctuators (ECMA-262, section 7.7, page 15). */                \
    T(LPAREN, "(", 0)                                                  \
    T(RPAREN, ")", 0)                                                  \
    T(LBRACK, "[", 0)                                                  \
    T(RBRACK, "]", 0)                                                  \
    T(LBRACE, "{", 0)                                                  \
    T(RBRACE, "}", 0)                                                  \
    T(COLON, ":", 0)                                                   \
    T(SEMICOLON, ";", 0)                                               \
    T(PERIOD, ".", 0)                                                  \
    T(ELLIPSIS, "...", 0)                                              \
    T(CONDITIONAL, "?", 3)                                             \
    T(INC, "++", 0)                                                    \
    T(DEC, "--", 0)                                                    \
    T(ARROW, "=>", 0)                                                  \
    \
    /* Assignment operators. */                                        \
    /* IsAssignmentOp() and Assignment::is_compound() relies on */     \
    /* this block of enum values being contiguous and sorted in the */ \
    /* same order! */                                                  \
    T(INIT_VAR, "=init_var", 2)                   /* AST-use only. */  \
    T(INIT_LET, "=init_let", 2)                   /* AST-use only. */  \
    T(INIT_CONST, "=init_const", 2)               /* AST-use only. */  \
    T(INIT_CONST_LEGACY, "=init_const_legacy", 2) /* AST-use only. */  \
    T(ASSIGN, "=", 2)                                                  \
    T(ASSIGN_BIT_OR, "|=", 2)                                          \
    T(ASSIGN_BIT_XOR, "^=", 2)                                         \
    T(ASSIGN_BIT_AND, "&=", 2)                                         \
    T(ASSIGN_SHL, "<<=", 2)                                            \
    T(ASSIGN_SAR, ">>=", 2)                                            \
    T(ASSIGN_SHR, ">>>=", 2)                                           \
    T(ASSIGN_ADD, "+=", 2)                                             \
    T(ASSIGN_SUB, "-=", 2)                                             \
    T(ASSIGN_MUL, "*=", 2)                                             \
    T(ASSIGN_DIV, "/=", 2)                                             \
    T(ASSIGN_MOD, "%=", 2)                                             \
    \
    /* Binary operators sorted by precedence. */                       \
    /* IsBinaryOp() relies on this block of enum values */             \
    /* being contiguous and sorted in the same order! */               \
    T(COMMA, ",", 1)                                                   \
    T(OR, "||", 4)                                                     \
    T(AND, "&&", 5)                                                    \
    T(BIT_OR, "|", 6)                                                  \
    T(BIT_XOR, "^", 7)                                                 \
    T(BIT_AND, "&", 8)                                                 \
    T(SHL, "<<", 11)                                                   \
    T(SAR, ">>", 11)                                                   \
    T(SHR, ">>>", 11)                                                  \
    T(ROR, "rotate right", 11) /* only used by Crankshaft */           \
    T(ADD, "+", 12)                                                    \
    T(SUB, "-", 12)                                                    \
    T(MUL, "*", 13)                                                    \
    T(DIV, "/", 13)                                                    \
    T(MOD, "%", 13)                                                    \
    \
    /* Compare operators sorted by precedence. */                      \
    /* IsCompareOp() relies on this block of enum values */            \
    /* being contiguous and sorted in the same order! */               \
    T(EQ, "==", 9)                                                     \
    T(NE, "!=", 9)                                                     \
    T(EQ_STRICT, "===", 9)                                             \
    T(NE_STRICT, "!==", 9)                                             \
    T(LT, "<", 10)                                                     \
    T(GT, ">", 10)                                                     \
    T(LTE, "<=", 10)                                                   \
    T(GTE, ">=", 10)                                                   \
    K(INSTANCEOF, "instanceof", 10)                                    \
    K(IN, "in", 10)                                                    \
    \
    /* Unary operators. */                                             \
    /* IsUnaryOp() relies on this block of enum values */              \
    /* being contiguous and sorted in the same order! */               \
    T(NOT, "!", 0)                                                     \
    T(BIT_NOT, "~", 0)                                                 \
    K(DELETE, "delete", 0)                                             \
    K(TYPEOF, "typeof", 0)                                             \
    K(VOID, "void", 0)                                                 \
    \
    /* Keywords (ECMA-262, section 7.5.2, page 13). */                 \
    K(BREAK, "break", 0)                                               \
    K(CASE, "case", 0)                                                 \
    K(CATCH, "catch", 0)                                               \
    K(CONTINUE, "continue", 0)                                         \
    K(DEBUGGER, "debugger", 0)                                         \
    K(DEFAULT, "default", 0)                                           \
    /* DELETE */                                                       \
    K(DO, "do", 0)                                                     \
    K(ELSE, "else", 0)                                                 \
    K(FINALLY, "finally", 0)                                           \
    K(FOR, "for", 0)                                                   \
    K(FUNCTION, "function", 0)                                         \
    K(IF, "if", 0)                                                     \
    /* IN */                                                           \
    /* INSTANCEOF */                                                   \
    K(NEW, "new", 0)                                                   \
    K(RETURN, "return", 0)                                             \
    K(SWITCH, "switch", 0)                                             \
    K(THIS, "this", 0)                                                 \
    K(THROW, "throw", 0)                                               \
    K(TRY, "try", 0)                                                   \
    /* TYPEOF */                                                       \
    K(VAR, "var", 0)                                                   \
    /* VOID */                                                         \
    K(WHILE, "while", 0)                                               \
    K(WITH, "with", 0)                                                 \
    \
    /* Literals (ECMA-262, section 7.8, page 16). */                   \
    K(NULL_LITERAL, "null", 0)                                         \
    K(TRUE_LITERAL, "true", 0)                                         \
    K(FALSE_LITERAL, "false", 0)                                       \
    T(NUMBER, NULL, 0)                                                 \
    T(SMI, NULL, 0)                                                    \
    T(STRING, NULL, 0)                                                 \
    \
    /* Identifiers (not keywords or future reserved words). */         \
    T(IDENTIFIER, NULL, 0)                                             \
    \
    /* Future reserved words (ECMA-262, section 7.6.1.2). */           \
    T(FUTURE_RESERVED_WORD, NULL, 0)                                   \
    T(FUTURE_STRICT_RESERVED_WORD, NULL, 0)                            \
    K(CLASS, "class", 0)                                               \
    K(CONST, "const", 0)                                               \
    K(EXPORT, "export", 0)                                             \
    K(EXTENDS, "extends", 0)                                           \
    K(IMPORT, "import", 0)                                             \
    K(LET, "let", 0)                                                   \
    K(STATIC, "static", 0)                                             \
    K(YIELD, "yield", 0)                                               \
    K(SUPER, "super", 0)                                               \
    \
    /* Illegal token - not able to scan. */                            \
    T(ILLEGAL, "ILLEGAL", 0)                                           \
    \
    /* Scanner-internal use only. */                                   \
    T(WHITESPACE, NULL, 0)                                             \
    T(UNINITIALIZED, NULL, 0)                                          \
    \
    /* ES6 Template Literals */                                        \
    T(TEMPLATE_SPAN, NULL, 0)                                          \
    T(TEMPLATE_TAIL, NULL, 0)

class Token
{

public:

#define T(name, string, precedence) name,
    enum Type {
        TOKEN_LIST(T, T)
        NUM_TOKENS
    };
#undef T

    // Returns a string corresponding to the C++ token name
    // (e.g. "LT" for the token LT).


    Token(Type t, std::string s):
        type(t),
        string(s) {

    }

    static Type findType(const std::string& name) {
        for(int iter=0; iter<NUM_TOKENS; iter++) {
            if(name_[iter] == name) {
                return (Type)iter;
            }
        }
        return IDENTIFIER;
    }

    static const char* Name(Type tok) {
        assert(tok < NUM_TOKENS);  // tok is unsigned
        return name_[tok];
    }

    // Predicates
    static bool IsKeyword(Type tok) {
        return token_type[tok] == 'K';
    }

    static bool IsIdentifier(Type tok) {
      return tok == IDENTIFIER;
    }

    //! [un-user]
    static bool IsAssignmentOp(Type tok) {
        return INIT_VAR <= tok && tok <= ASSIGN_MOD;
    }
    //! [un-user]

    static bool IsBinaryOp(Type op) {
        return COMMA <= op && op <= MOD;
    }

    static bool IsTruncatingBinaryOp(Type op) {
        return BIT_OR <= op && op <= ROR;
    }

    // 比较运算符
    static bool IsCompareOp(Type op) {
        return EQ <= op && op <= IN;
    }

    // 有序关系比较
    static bool IsOrderedRelationalCompareOp(Type op) {
        return op == LT || op == LTE || op == GT || op == GTE;
    }

    static bool IsEqualityOp(Type op) {
        return op == EQ || op == EQ_STRICT;
    }

    // 不等式
    static bool IsInequalityOp(Type op) {
        return op == NE || op == NE_STRICT;
    }

    // 比较运算符
    static bool IsArithmeticCompareOp(Type op) {
        return IsOrderedRelationalCompareOp(op) ||
                IsEqualityOp(op) || IsInequalityOp(op);
    }

    // 反转比较运算符
    static Type NegateCompareOp(Type op) {
        assert(IsArithmeticCompareOp(op));
        switch (op) {
        case EQ: return NE;
        case NE: return EQ;
        case EQ_STRICT: return NE_STRICT;
        case NE_STRICT: return EQ_STRICT;
        case LT: return GTE;
        case GT: return LTE;
        case LTE: return GT;
        case GTE: return LT;
        default:
            return op;
        }
    }

    // 反转比较运算符
    static Type ReverseCompareOp(Type op) {
        assert(IsArithmeticCompareOp(op));
        switch (op) {
        case EQ: return EQ;
        case NE: return NE;
        case EQ_STRICT: return EQ_STRICT;
        case NE_STRICT: return NE_STRICT;
        case LT: return GT;
        case GT: return LT;
        case LTE: return GTE;
        case GTE: return LTE;
        default:
            return op;
        }
    }

    // 位操作运算符
    static bool IsBitOp(Type op) {
        return (BIT_OR <= op && op <= SHR) || op == BIT_NOT;
    }

    // 一元运算符
    static bool IsUnaryOp(Type op) {
        return (NOT <= op && op <= VOID) || op == ADD || op == SUB;
    }

    // 自加自减运算符
    static bool IsCountOp(Type op) {
        return op == INC || op == DEC;
    }

    // 位移运算符
    static bool IsShiftOp(Type op) {
        return (SHL <= op) && (op <= SHR);
    }

    // Returns a string corresponding to the JS token string
    // (.e., "<" for the token LT) or NULL if the token doesn't
    // have a (unique) string (e.g. an IDENTIFIER).
    static const char* String(Type tok) {
        assert(tok > NUM_TOKENS);  // tok is unsigned.
        return string_[tok];
    }

    // Returns the precedence > 0 for binary and compare
    // operators; returns 0 otherwise.
    static int Precedence(Type tok) {
        assert(tok < NUM_TOKENS);  // tok is unsigned.
        return precedence_[tok];
    }

    Type type;
    std::string string;

protected:
    static const char* const name_[NUM_TOKENS];
    static const char* const string_[NUM_TOKENS];
    static const int precedence_[NUM_TOKENS];
    static const char token_type[NUM_TOKENS];

};

typedef std::list<Token> TokenList;


}

#endif // TOKEN_H
