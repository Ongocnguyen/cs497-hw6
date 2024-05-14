#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Evaluator;

    class IndexOp : public Object {
    public:
        IndexOp(Object* collection, Object* index);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _collection;
        Object* _index;
    };

}
