#include <plx/expr/Throw.hpp>

namespace PLX {

    Throw::Throw(Object* expr)
        : _expr {expr}
    {}

    Object* Throw::eval(Evaluator* etor) {
        (void)etor;
        throw _expr;
    }

    void Throw::markChildren() {
        _expr->mark();
    }

    void Throw::showOn(std::ostream& ostream) const {
        ostream << "throw " << _expr;
    }

    TypeId Throw::typeId() const {
        return TypeId::E_THROW;
    }

}
