#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Evaluator;
    class Apply;
    class Identifier;

    class BinOpExpr : public Object {
    public:
        BinOpExpr(Object* lhs, Identifier* oper, Object* rhs);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _lhs;
        Identifier* _operator;
        Object* _rhs;
        Apply* _apply;
    };

}
