#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;
    class Triple;
    class Function;

    class Closure : public Object {
    public:
        Closure(Function* function, Triple* lexicalEnvironment, bool isMacro);

        // Overridden functions --------------------------------------------

        Object* apply(Evaluator* etor, List* arguments) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        Function* _function;
        Triple* _lexicalEnvironment;
        bool _isMacro;
    };

}
