#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_HashTable {

        Object* keys(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("keys", etor, args, {TypeId::D_HASHTABLE});
            HashTable* hashTable = static_cast<HashTable*>(argVals->first());
            Array* keys = hashTable->keys();
            return keys;
        }

    }
}
