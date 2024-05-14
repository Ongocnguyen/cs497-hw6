#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {

    List* evalArgs(Evaluator* etor, List* args) {
        Object* res = etor->evalExpr(args);
        assert(res->isA(TypeId::D_LIST));
        List* argValues = static_cast<List*>(res);
        return argValues;
    }

    void argumentCountMismatch(const std::string& name, int nExpectedArgs, int nActualArgs) {
        throwException(name, "Arguemnt count mismatch",
            new Array({new Triple(Symbol::create("Expected"), new Integer(nExpectedArgs)),
                        new Triple(Symbol::create("Actual"), new Integer(nActualArgs))}));
    }

    List* evalNArgs(const std::string& name, Evaluator* etor, List* args, std::initializer_list<TypeId> types) {
        int nExpectedArgs = types.size();
        int nActualArgs = args->length();
        if (nExpectedArgs != nActualArgs) {
            argumentCountMismatch(name, nExpectedArgs, nActualArgs);
        }
        Queue* argVals = new Queue();
        for (TypeId type : types) {
            Object* arg = args->first();
            Object* argVal = etor->evalExpr(arg);
            if (type != TypeId::Z_ANY) {
                if (!argVal->isA(type)) {
                    throwException(name, "Arguemnt type mismatch",
                        new Array({new Triple(Symbol::create("Expected"), Symbol::create(TYPE_NAMES[type])),
                                new Triple(Symbol::create("Actual"), Symbol::create(TYPE_NAMES[argVal->typeId()]))}));
                }
            }
            argVals->enq(argVal);
            args = args->restAsList();
        }
        return argVals->asList();
    }

}
