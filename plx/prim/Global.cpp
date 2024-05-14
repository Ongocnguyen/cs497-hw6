#include <cassert>

#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Boolean.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_Global {

        Object* argMap(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "argMap";
            evalNArgs(PRIM_NAME, etor, args, {});
            return GLOBALS->ArgMap();
        }

        Object* eval(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "eval";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* argVal = argVals->first();
            return etor->evalExpr(argVal);
        }

        Object* notOperator(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "not";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* arg = argVals->first();
            return arg->boolValue() ? GLOBALS->False() : GLOBALS->True();
        }

        Object* repl(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "repl";
            std::clog << PRIM_NAME << " args = " << args << "\n";
            std::clog << "primitive is not implemented fully\n";
            (void)etor;
            return GLOBALS->NilObject();
        }

        Object* type(Evaluator* etor, List* args) {
            const std::string PRIM_NAME = "type";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* arg = argVals->first();
            return Symbol::create(arg->typeName());
        }

    }
}
