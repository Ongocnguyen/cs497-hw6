#include <plx/data/Triple.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/NamedFunction.hpp>

namespace PLX {

    NamedFunction::NamedFunction(Identifier* name, Function* function)
        : _name {name}
        , _function {function}
        , _let {new Let(new Triple(_name, _function))}
    {}

    Object* NamedFunction::eval(Evaluator* etor) {
        return _let->eval(etor);
    }

    void NamedFunction::markChildren() {
        _let->mark();
    }

    void NamedFunction::showOn(std::ostream& ostream) const {
        ostream << "fun "
                << _name;
        _function->showRulesOn(ostream);
    }

    TypeId NamedFunction::typeId() const {
        return TypeId::E_NAMEDFUNCTION;
    }

}