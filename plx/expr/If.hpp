#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class If : public Object {
    public:
        If(Object* cond, Object* conseq, Object* alt);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _cond;
        Object* _conseq;
        Object* _alt;
    };

}
