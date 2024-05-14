#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class Triple;
    class Evaluator;

    class Let : public Object {
    public:
        Let(Triple* bindings);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Triple* _bindings;
    };

}
