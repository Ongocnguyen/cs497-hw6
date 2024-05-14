#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Method.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/evaluator/Evaluator.hpp>

namespace PLX {

    Method::Method(Object* lhs, Identifier* rhs)
        : _lhs {lhs}
        , _rhs {rhs}
    {}

    Object* Method::apply(Evaluator* etor, List* arguments) {
        List* arguments1 = new List(_lhs, arguments);
        Object* rhsVal = etor->evalExpr(_rhs);
        Apply* app = new Apply(rhsVal, arguments1);
        return etor->evalExpr(app);
    }

    List* Method::freeVars(List* freeVars) {
        return _lhs->freeVars(_rhs->freeVars(freeVars));
    }

    void Method::markChildren() {
        _lhs->mark();
        _rhs->mark();
    }

    void Method::showOn(std::ostream& ostream) const {
        ostream << _lhs << '.' << _rhs;
    }

    TypeId Method::typeId() const {
        return TypeId::D_METHOD;
    }

}
