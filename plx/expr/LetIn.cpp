#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/LetIn.hpp>

namespace PLX {

    LetIn::LetIn(Triple* bindings, Object* body)
        : _let {new Let(bindings)}
        , _body {body}
    {}

    Object* LetIn::eval(Evaluator* etor) {
        Triple* savedEnv = etor->environment();
        etor->evalExpr(_let);
        Object* value = etor->evalExpr(_body);
        etor->setEnvironment(savedEnv);
        return value;
    }

    void LetIn::markChildren() {
        _let->mark();
        _body->mark();
    }

    void LetIn::showOn(std::ostream& ostream) const {
        ostream << _let
                << " in "
                << _body;
    }

    TypeId LetIn::typeId() const {
        return TypeId::E_LETIN;
    }

}