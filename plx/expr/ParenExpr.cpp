#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/ParenExpr.hpp>

namespace PLX {

    ParenExpr::ParenExpr(Object* expr)
        : _expr {expr}
    {}

    Object* ParenExpr::eval(Evaluator* etor) {
        return etor->evalExpr(_expr);
    }

    void ParenExpr::markChildren() {
        _expr->mark();
    }

    void ParenExpr::showOn(std::ostream& ostream) const {
        ostream << '(' <<_expr << ')';
    }

    TypeId ParenExpr::typeId() const {
        return TypeId::E_PARENEXPR;
    }

}
