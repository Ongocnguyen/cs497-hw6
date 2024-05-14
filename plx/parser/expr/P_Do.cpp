#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/Do.hpp>
#include <plx/object/Object.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
namespace PLX {
bool pDo(List*& tokens, Object*& value) {
    Queue* expressions = new Queue();

    // Parse 'do' keyword
    Object* ignore;
    if (!pReservedDo(tokens, ignore)) {
        return false;
    }

    // Parse multiple expressions
    while (true) {
        Object* expr;
        if (!pAny(tokens, expr)) {
            break; // No more expressions to parse
        }
        expressions->enq(expr);
    }

    // Parse 'end' keyword
    if (!pReservedEnd(tokens, ignore)) {
        delete expressions;
        return false;
    }

    // Create and return a new Do expression
    value = new Do(expressions->asList());
    delete expressions;
    return true;
}
}
