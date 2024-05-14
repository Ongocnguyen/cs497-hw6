#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class Do;
    class Evaluator;
    class Let;
    class Triple;

    class LetIn : public Object {
    public:
        LetIn(Triple* bindings, Object* body);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Let* _let;
        Object* _body;
    };

}
