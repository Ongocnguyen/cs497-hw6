#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/TryCatch.hpp>
#include <plx/literal/Nil.hpp>

namespace PLX {

    TryCatch::TryCatch(Object* expr, Triple* catchRules)
        : TryCatch{expr, catchRules, GLOBALS->NilObject()}
    {}

    TryCatch::TryCatch(Object* expr, Triple* catchRules, Object* finally)
        : _expr {expr}
        , _catchRules {catchRules}
        , _finally {finally}
    {}

    Object* TryCatch::eval(Evaluator* etor) {
        Object* value;
        bool rethrow = false;
        Object* rethrowException = GLOBALS->NilObject();
        try {
            value = etor->evalExpr(_expr);
        }
        catch (Object* exception) {
            Triple* env = etor->environment();
            if (_catchRules->matchLocate(exception, value, env)) {
                etor->evalExpr(value, env);
            }
            else {
                rethrowException = exception;
                rethrow = true;
            }
        }
        etor->evalExpr(_finally);
        if (rethrow) {
            throw rethrowException;
        }
        return value;
    }

    void TryCatch::markChildren() {
        _expr->mark();
        _catchRules->mark();
        _finally->mark();
    }

    void TryCatch::showOn(std::ostream& ostream) const {
        ostream << "try "
            << _expr
            << " catch ";
        _catchRules->showOnWith(ostream, " | ");
        if (_finally != GLOBALS->NilObject()) {
            ostream << " finally " << _finally;
        }
        ostream << " end";
    }

    TypeId TryCatch::typeId() const {
        return TypeId::E_TRYCATCH;
    }

}
