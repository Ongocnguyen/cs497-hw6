#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;

    class TryCatch : public Object {
    public:
        TryCatch(Object* expr, Triple* catchRules);
        TryCatch(Object* expr, Triple* catchRules, Object* finally);

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Object* _expr;
        Triple* _catchRules;
        Object* _finally;

    };

}
