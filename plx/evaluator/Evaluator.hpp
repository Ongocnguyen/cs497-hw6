#pragma once

#include <plx/object/Object.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    class Triple;
    class Identifier;

    class Evaluator : public Object {
    public:
        Evaluator();

        // Unique functions ------------------------------------------------

        Triple* bind(Object* key, Object* value);
        Triple* environment() const;
        Object* evalExpr(Object* expr);
        Object* evalExpr(Object* expr, Triple* environment);
        Object* lookup(Identifier* key) const;
        bool rebind(Identifier* key, Object* value);
        void setEnvironment(Triple* env);

        // Overridden functions --------------------------------------------

        void markChildren() override;
        TypeId typeId() const override;
    
    private:
        Triple* _environment {GLOBALS->EmptyTriple()};
        void _definePrims();
    
    };

}
