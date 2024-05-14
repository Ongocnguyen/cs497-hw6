#include <cassert>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_Any.hpp>
#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/If.hpp>
#include <plx/object/Object.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_Any.hpp>

namespace PLX {

bool pIf(List*& tokens, Object*& value) {
    // Parse the reserved word "if"
    Object* ignore;
    if (!pReservedIf(tokens, ignore)) {
        return false;
    }

    // Parse the condition expression
    Object* condition;
    if (!pRequireAny(tokens, condition)) {
        return false;
    }

    // Parse the reserved word "then"
    if (!pReservedThen(tokens, ignore)) {
        return false;
    }

    // Parse the consequent expression
    Object* consequent;
    if (!pRequireAny(tokens, consequent)) {
        return false;
    }

    // Parse the reserved word "else"
    if (!pReservedElse(tokens, ignore)) {
        return false;
    }

    // Parse the alternate expression
    Object* alternate;
    if (!pRequireAny(tokens, alternate)) {
        return false;
    }

    // Create a new If instance with the parsed condition, consequent, and alternate
    value = new If(condition, consequent, alternate);

    return true;
}
}
