#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    class List;

    class Function : public Object {
    public:
        Function();
        Function(List* parameters, Object* body);

        // Unique functions ------------------------------------------------

        bool isEmpty() const;
        Object* matchArgumentsToParameters(List* arguments, Triple*& lexicalEnvironment);
        void setNext(Function* next);

        void showRulesOn(std::ostream& ostream) const;

        // Overridden functions --------------------------------------------

        Object* eval(Evaluator* etor) override;
        void markChildren() override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

        friend class NamedFunction;

    private:
        List* _parameters;
        Object* _body;
        Function* _next;
    };

}
