#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/If.hpp>

namespace PLX {

    If::If(Object* cond, Object* conseq, Object* alt)
        : _cond {cond}
        , _conseq {conseq}
        , _alt {alt}
    {}

    Object* If::eval(Evaluator* etor) {
        Object* condRes = etor->evalExpr(_cond);
        return condRes->boolValue()
             ? etor->evalExpr(_conseq)
             : etor->evalExpr(_alt);
    }

    void If::markChildren() {
        _cond->mark();
        _conseq->mark();
        _alt->mark();
    }

    void If::showOn(std::ostream& ostream) const {
        ostream << "if "
                << _cond
                << " then "
                << _conseq
                << " else "
                << _alt;
    }

    TypeId If::typeId() const {
        return TypeId::E_IF;
    }

}
