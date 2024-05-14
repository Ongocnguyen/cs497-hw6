#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>

namespace PLX {

    Apply::Apply(Object* abstractionObj, List* arguments)
        : _abstractionObj {abstractionObj}
        , _arguments {arguments}
    {}

    Object* Apply::eval(Evaluator* etor) {
        Object* abstractionValue = etor->evalExpr(_abstractionObj);
        return abstractionValue->apply(etor, _arguments);

    }

    void Apply::markChildren() {
        _abstractionObj->mark();
        _arguments->mark();
    }

    void Apply::showOn(std::ostream& ostream) const {
        switch (_abstractionObj->typeId()) {
            case TypeId::D_CLOSURE:
            case TypeId::E_FUNCTION:
            case TypeId::E_NAMEDFUNCTION:
                ostream << '(' << _abstractionObj << ')';
                break;
            default:
                ostream << _abstractionObj;
                break;
        }
        _arguments->showOnWith(ostream, "(", ", ", ")");
    }

    TypeId Apply::typeId() const {
        return TypeId::E_APPLY;
    }

}
