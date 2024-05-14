#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_Array {

        Object* get(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("get", etor, args, {TypeId::D_ARRAY, TypeId::L_INTEGER});
            Array* array = static_cast<Array*>(argVals->first());
            Integer* index = static_cast<Integer*>(argVals->second());
            Object* value;
            assert(array->index(index, value));
            return value;
        }

        Object* set(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("get", etor, args, {TypeId::D_ARRAY, TypeId::L_INTEGER, TypeId::Z_ANY});
            Array* array = static_cast<Array*>(argVals->first());
            Integer* index = static_cast<Integer*>(argVals->second());
            Object* value = argVals->third();
            array->set(index->value(), value);
            assert(array->index(index, value));
            return array;
        }

    }
}
