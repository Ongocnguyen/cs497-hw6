#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;

    class Do : public Object {
    public:
        Do(List* exprs);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        List* _exprs;
        List* _reverseExprs;
     };

}
