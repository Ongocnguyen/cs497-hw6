#pragma once

#include <list>

#include <plx/object/Object.hpp>

namespace PLX {

    class Evaluator;
    class Identifier;
    class List;

    class Method : public Object {
    public:
        Method(Object* lhs, Identifier* rhs);

        // Unique functions ------------------------------------------------

        // Overridden functions --------------------------------------------

        Object* apply(Evaluator* etor, List* arguments) override;
        List* freeVars(List* freeVars) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _lhs;
        Identifier* _rhs;
    };

}
