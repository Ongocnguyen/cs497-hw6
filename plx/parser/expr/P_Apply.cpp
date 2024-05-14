#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/object/Object.hpp>
#include <plx/parser/expr/P_Expr.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_SpecialChars.hpp>
#include <plx/parser/Parser.hpp>
#include <plx/parser/expr/P_Identifier.test.cpp>
#include <plx/parser/expr/P_ParenExpr.cpp>
#include <plx/parser/P_Any.hpp>
namespace PLX {

bool pApply(List*& tokens, Object*& value) {
    static const std::initializer_list<Parser> parserList {
            pIdentifier,
            pParenExpr
        };
    // Parse identifier
    Identifier* identifier;
    if (pIdentifier(tokens, identifier)) {
        // Parse argument list
        Queue* args;
        if (!pArgumentList(tokens, args)) {
            return false;
        }
        // Create and return Apply instance
        value = new Apply(identifier, args->asList());
        return true;
    }
    
    //Parse parenthesized expression
    ParenExpr* parenExpr;
    if (pParenExpr(tokens, parenExpr)) {
        // Parse argument list
        Queue* args;
        if (!pArgumentList(tokens, args)) {
            return false;
        }
        // Create and return Apply instance
        value = new Apply(parenExpr, args->asList());
        return true;
    }

    // Neither identifier nor parenthesized expression found
    return false;
}
}