#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Match.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Match::Match(Object* expression, Triple* rules)
        : _expression {expression}
        , _rules {rules}
    {}

    Object* Match::eval(Evaluator* etor) {
        Object* exprValue = etor->evalExpr(_expression);
        Triple* rules = _rules;
        Triple* env = etor->environment();
        Object* value;
        if (!rules->matchLocate(exprValue, value, env)) {
            throwException("Match::eval", "Argument mismatch", new Array({exprValue, this}));
        }
        return value;
    }

    void Match::markChildren() {
        _expression->mark();
        _rules->mark();
    }

    void Match::showOn(std::ostream& ostream) const {
        ostream << "match " << _expression << " in ";
        _rules->showOnWith(ostream, " | ");
        ostream << " end";
    }

    TypeId Match::typeId() const {
        return TypeId::E_MATCH;
    }

}