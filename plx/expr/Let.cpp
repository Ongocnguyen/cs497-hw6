#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/Let.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Let::Let(Triple* bindings)
        : _bindings {bindings}
    {}

    void prebindFreeVars(Object* lhs, Evaluator* etor) {
        List* freeVars = lhs->freeVars(GLOBALS->EmptyList());
        while (!freeVars->isEmpty()) {
            assert(freeVars->first()->isA(TypeId::E_IDENTIFIER));
            Identifier* ident = static_cast<Identifier*>(freeVars->first());
            etor->bind(ident, GLOBALS->NilObject());
            freeVars = freeVars->restAsList();
        }
    }

    void matchLhsToRhsVal(Object* lhs, Object* rhsVal, Evaluator* etor) {
        Triple* newBindings = GLOBALS->EmptyTriple();
        if (!lhs->match(rhsVal, newBindings)) {
            throwException("Let", "Match failure", new Array({lhs, rhsVal}));
        }
        // for each binding in the LHS, re-bind the value in the env
        while (!newBindings->isEmpty()) {
            assert(newBindings->key()->isA(TypeId::E_IDENTIFIER));
            Identifier* ident = static_cast<Identifier*>(newBindings->key());
            Object* newValue = newBindings->value();
            etor->rebind(ident, newValue);
            newBindings = newBindings->next();
        }
    }

    Object* Let::eval(Evaluator* etor) {
        Triple* bindings = _bindings;
        while (!bindings->isEmpty()) {
            Object* lhs = bindings->key();
            prebindFreeVars(lhs, etor);
            Object* rhs = bindings->value();
            Object* rhsVal = etor->evalExpr(rhs);
            matchLhsToRhsVal(lhs, rhsVal, etor);
            bindings = bindings->next();
        }
        return GLOBALS->NilObject();
    }

    void Let::markChildren() {
        _bindings->mark();
    }

    void Let::showOn(std::ostream& ostream) const {
        ostream << "let " << _bindings;
    }

    TypeId Let::typeId() const {
        return TypeId::E_LET;
    }

}