#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/object/Object.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/expr/P_Expr.hpp>
#include <plx/parser/P_SpecialChars.hpp>
#include <plx/parser/P_Any.hpp>
namespace PLX {


bool pLet(List*& tokens, Object*& value) {
  bool pIdentifier(List*& tokens, Object*& value);  
    // Parse the reserved word "let"
    Object* ignore;
    if (!pReservedLet(tokens, ignore)) {
        return false;
    }

    // Parse the identifier
    Object* identifier;
    if (!pIdentifier(tokens, identifier)) {
        return false;
    }

    // Parse the equals sign
    if (!pIgnoreEquals(tokens, ignore)) {
        return false;
    }

    // Parse the expression
    Object* expression;
    if (!pRequireAny(tokens, expression)) {
        return false;
    }

    Triple* bindings = new Triple(identifier, expression, nullptr);
    Object* body = nullptr;
    // Check if there's an "in" keyword
    if (pReservedIn(tokens, ignore)) {
        // Parse the body expression
       
        if (!pRequireAny(tokens, body)) {
            return false;
        }
        // Create Let instance
        value = new Let(bindings);
    } else {
        // Create LetIn instance
        value = new LetIn(bindings, body);
    }

    return true;
}
}