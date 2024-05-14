#pragma once

#include <plx/object/Object.hpp>

namespace PLX {

    typedef Object* (*Primitive)(Evaluator* etor, List* arguments);

    class PrimitiveFunction : public Object {
    public:
        PrimitiveFunction(const std::string& name, Primitive primitive);

        // Unique functions ------------------------------------------------

        std::string name();
    
        // Overridden functions --------------------------------------------

        Object* apply(Evaluator* etor, List* arguments) override;
        bool hashCode(HashCode& hashCode) override;
        void showOn(std::ostream& ostream) const override;
        TypeId typeId() const override;

    private:
        std::string _name;
        Primitive _primitive;

    };

}
