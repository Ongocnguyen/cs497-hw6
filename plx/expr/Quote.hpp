#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class Quote : public Object {
    public:

        Quote(Object* expr);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        bool hashCode(HashCode& hashCode) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _expr;

    };

}
