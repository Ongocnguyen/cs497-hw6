#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_List {

        Object* first(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("first", etor, args, {TypeId::D_LIST});
            List* list = static_cast<List*>(argVals->first());
            return list->first();
        }

        Object* rest(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("rest", etor, args, {TypeId::D_LIST});
            List* list = static_cast<List*>(argVals->first());
            return list->rest();
        }

        Object* setFirst(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("setFirst", etor, args, {TypeId::D_LIST, TypeId::Z_ANY});
            List* list = static_cast<List*>(argVals->first());
            Object* elem = argVals->second();
            list->setFirst(elem);
            return list;
        }

        Object* setRest(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("setRest", etor, args, {TypeId::D_LIST, TypeId::Z_ANY});
            List* list = static_cast<List*>(argVals->first());
            Object* elem = argVals->second();
            list->setRest(elem);
            return list;
        }

    }
}
