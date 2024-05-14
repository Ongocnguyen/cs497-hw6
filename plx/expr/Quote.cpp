#include <plx/expr/Quote.hpp>
#include <plx/evaluator/Evaluator.hpp>

namespace PLX {

    Quote::Quote(Object* expr)
        : _expr {expr}
    {}

    Object* Quote::eval(Evaluator* etor) {
        (void)etor;
        return _expr;
    }

    bool Quote::hashCode(HashCode& hashCode) {
        static const int typeHashCode = std::hash<int>{}(static_cast<int>(typeId()));
        HashCode exprHashCode;
        if (_expr->hashCode(exprHashCode)) {
            hashCode = typeHashCode ^ exprHashCode;
            return true;
        }
        return false;
    }

    void Quote::markChildren() {
        _expr->mark();
    }

    void Quote::showOn(std::ostream& ostream) const {
        ostream << '\'' << _expr << '\'';
    }

    TypeId Quote::typeId() const {
        return TypeId::E_QUOTE;
    }

}
