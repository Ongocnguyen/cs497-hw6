#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/DefinePrims.hpp>

namespace PLX {

    bool globalEvaluatorDebug = false;

    Evaluator::Evaluator() {
        definePrims(this);
    }

    Triple* Evaluator::bind(Object* key, Object* value) {
        _environment = new Triple(key, value, _environment);
        return _environment;
    }

    Triple* Evaluator::environment() const {
        return _environment;
    }

    Object* Evaluator::evalExpr(Object* expr) {
        // TODO this is where you can add instrumentation (i.e. print things)
        // or check for a Trampoline.
        if (globalEvaluatorDebug) {
            std::clog << "Evaluator::evalExpr " << expr << " :: " << expr->typeName() << '\n';
        }
        return expr->eval(this);
    }

    Object* Evaluator::evalExpr(Object* expr, Triple* environment) {
        Triple* savedEnv = _environment;
        _environment = environment;
        Object* value = evalExpr(expr);
        _environment = savedEnv;
        return value;
    }

    Object* Evaluator::lookup(Identifier* identifier) const {
        Object* value;
        if (!_environment->lookup(identifier, value)) {
            throwException("Evaluator", "Unbound identifier", identifier);
        }
        return value;
    }

    void Evaluator::markChildren() {
        _environment->mark();
    }

    bool Evaluator::rebind(Identifier* key, Object* value) {
        Triple* binding = _environment->locate(key);
        if (binding->isEmpty()) {
            return false;
        }
        binding->setValue(value);
        return false;
    }


    void Evaluator::setEnvironment(Triple* env) {
        _environment = env;
    }

    TypeId Evaluator::typeId() const {
        return TypeId::T_EVALUATOR;
    }

}
