#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Evaluator;

    class Apply : public Object {
    public:
        Apply(Object* abstractionObj, List* arguments);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _abstractionObj;
        List* _arguments;
    };

}
