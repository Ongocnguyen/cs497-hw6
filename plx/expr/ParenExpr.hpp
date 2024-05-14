#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class ParenExpr : public Object {
    public:

        ParenExpr(Object* expr);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _expr;

    };

}
