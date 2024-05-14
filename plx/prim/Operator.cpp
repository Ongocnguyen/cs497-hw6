#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Method.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Boolean.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {

    namespace Prim_Operator {

        void operationNotSupported(std::string primName, Object* lhs, Object* rhs) {
            throwException(primName, "Operation not supported for arguments",
                new Array({
                    new Array({lhs, Symbol::create(lhs->typeName())}),
                    new Array({rhs, Symbol::create(rhs->typeName())}),
                }));
        }

        Object* bind(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME {"/"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Triple* binding = new Triple(lhs, rhs);
            return binding;
        }

        Object* divide(Evaluator* etor, List* args) {
            const std::string PRIM_NAME {"/"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Object* value;
            if (!lhs->divide(rhs, value)) {
                operationNotSupported(PRIM_NAME, lhs, rhs);
            }
            return value;
        }

        Object* dot(Evaluator* etor, List* args) {
            (void)etor;
            const std::string PRIM_NAME {"."};
            int nArgs = args->length();
            if (nArgs != 2) {
                argumentCountMismatch(PRIM_NAME, 2, nArgs);
            }
            Object* lhs = args->first();
            Object* rhs = args->second();
            assert(rhs->typeId() == TypeId::E_IDENTIFIER);
            Identifier* rhsIdent = static_cast<Identifier*>(rhs);
            Method* method = new Method(lhs, rhsIdent);
            return method;
        }

        Object* equalTo(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "==";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argVals->first();
            Object* rhs = argVals->second();
            return (*lhs == *rhs) ? GLOBALS->True() : GLOBALS->False();
        }

        Object* minus(Evaluator* etor, List* args) {
            const std::string PRIM_NAME {"-"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Object* value;
            if (!lhs->minus(rhs, value)) {
                operationNotSupported(PRIM_NAME, lhs, rhs);
            }
            return value;
        }

        Object* plus(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME {"+"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Object* value;
            if (!lhs->plus(rhs, value)) {
                operationNotSupported(PRIM_NAME, lhs, rhs);
            }
            return value;
        }

        Object* percent(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME {"+"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Object* value;
            if (!lhs->percent(rhs, value)) {
                operationNotSupported(PRIM_NAME, lhs, rhs);
            }
            return value;
        }

        Object* times(Evaluator* etor, List* args) {
            const std::string PRIM_NAME {"*"};
            List* argValues = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY, TypeId::Z_ANY});
            Object* lhs = argValues->first();
            Object* rhs = argValues->second();
            Object* value;
            if (!lhs->times(rhs, value)) {
                operationNotSupported(PRIM_NAME, lhs, rhs);
            }
            return value;
        }

    }
}
