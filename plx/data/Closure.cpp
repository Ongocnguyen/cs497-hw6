#include <cassert>

#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>

namespace PLX {

    Closure::Closure(Function* function, Triple* lexicalEnvironment, bool isMacro)
        : _function {function}
        , _lexicalEnvironment {lexicalEnvironment}
        , _isMacro {isMacro}
    {}

    Object* Closure::apply(Evaluator* etor, List* arguments) {
        List* argValues;
        if (_isMacro) {
            argValues = arguments;
        }
        else {
            Object* argValueObj = etor->evalExpr(arguments);
            assert(argValueObj->isA(TypeId::D_LIST));
            argValues = static_cast<List*>(argValueObj);
        }
        Triple* newEnvironment = _lexicalEnvironment;
        Object* body = _function->matchArgumentsToParameters(argValues, newEnvironment);
        Object* value = etor->evalExpr(body, newEnvironment);
        return value;
    }

    void Closure::markChildren() {
        _function->mark();
        _lexicalEnvironment->mark();
    }

    void Closure::showOn(std::ostream& ostream) const {
        ostream << _function;
    }

    TypeId Closure::typeId() const {
        return TypeId::D_CLOSURE;
    }

}