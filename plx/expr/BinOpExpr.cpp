#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/expr/BinOpExpr.hpp>
#include <plx/expr/Identifier.hpp>

namespace PLX {

    BinOpExpr::BinOpExpr(Object* lhs, Identifier* oper, Object* rhs)
        : _lhs {lhs}
        , _operator {oper}
        , _rhs {rhs}
        , _apply {new Apply(oper, List::create({lhs, rhs}))}
    {}

    Object* BinOpExpr::eval(Evaluator* etor) {
        Object* res = etor->evalExpr(_apply);
        return res;
    }

    void BinOpExpr::markChildren() {
        _lhs->mark();
        _operator->mark();
        _rhs->mark();
        _apply->mark();
    }

    void BinOpExpr::showOn(std::ostream& ostream) const {
        std::string opName {_operator->name()};
        if (opName == ".") {
            ostream << _lhs << opName << _rhs;
        }
        else {
            ostream << _lhs << ' ' << opName << ' ' << _rhs;
        }
    }

    TypeId BinOpExpr::typeId() const {
        return TypeId::E_BINOPEXPR;
    }

}
