#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Function::Function()
        : _parameters {GLOBALS->EmptyList()}
        , _body {GLOBALS->NilObject()}
        , _next {this}
    {}

    Function::Function(List* parameters, Object* body)
        : _parameters {parameters}
        , _body {body}
        , _next {GLOBALS->EmptyFunction()}
    {}

    Object* Function::eval(Evaluator* etor) {
        return new Closure(this, etor->environment(), false);
    }

    bool Function::isEmpty() const {
        return this == GLOBALS->EmptyFunction();
    }

    void Function::markChildren() {
        _parameters->mark();
        _body->mark();
    }

    Object* Function::matchArgumentsToParameters(List* arguments, Triple*& lexicalEnvironment) {
        Function* rule = this;
        while (!rule->isEmpty()) {
            Triple* tempEnv = lexicalEnvironment;
            if (rule->_parameters->match(arguments, tempEnv)) {
                lexicalEnvironment = tempEnv;
                return rule->_body;
            }
            rule = rule->_next;
        }
        throwException("Function", "Argument mismatch", new Array({arguments, this}));
        return this;  // keep the compiler happy
    }

    void Function::setNext(Function* next) {
        _next = next;
    }

    void Function::showOn(std::ostream& ostream) const {
        ostream << "fun ";
        showRulesOn(ostream);
    }

    void Function::showRulesOn(std::ostream& ostream) const {
        const Function* functionRule = this;
        bool firstIter = true;
        while (!functionRule->isEmpty()) {
            if (firstIter) {
                firstIter = false;
            }
            else {
                ostream << " | ";
            }
            functionRule->_parameters->showOnWith(ostream, "(", ", ", ")");
            ostream << " = " << functionRule->_body;
            functionRule = functionRule->_next;
        }
    }

    TypeId Function::typeId() const {
        return TypeId::E_FUNCTION;
    }

}