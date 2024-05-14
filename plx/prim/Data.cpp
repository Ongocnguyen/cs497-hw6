#include <cassert>
#include <sstream>

#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_Data {

        Object* length(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME = "length";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* elem = argVals->first();
            int len;
            if (!elem->length(len)) {
                throwException(PRIM_NAME, "Illegal argument type",
                    new Array({new Triple(Symbol::create("Value"), elem),
                               new Triple(Symbol::create("Type"), Symbol::create(elem->typeName()))}));
            }
            return new Integer(len);
        }

        Object* toArray(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME = "toArray";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* elem = argVals->first();
            Array* array;
            if (!elem->toArray(array)) {
                throwException(PRIM_NAME, "Illegal argument type",
                    new Array({new Triple(Symbol::create("Value"), elem),
                               new Triple(Symbol::create("Type"), Symbol::create(elem->typeName()))}));
            }
            return array;
        }

        Object* toList(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME = "toList";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* elem = argVals->first();
            List* list;
            if (!elem->toList(list)) {
                throwException(PRIM_NAME, "Illegal argument type",
                    new Array({new Triple(Symbol::create("Value"), elem),
                               new Triple(Symbol::create("Type"), Symbol::create(elem->typeName()))}));
            }
            return list;
        }

        Object* toQueue(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME = "toQueue";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* elem = argVals->first();
            Queue* queue;
            if (!elem->toQueue(queue)) {
                throwException(PRIM_NAME, "Illegal argument type",
                    new Array({new Triple(Symbol::create("Value"), elem),
                               new Triple(Symbol::create("Type"), Symbol::create(elem->typeName()))}));
            }
            return queue;
        }

        Object* toString(Evaluator* etor, List* args) {
            static const std::string PRIM_NAME = "toString";
            List* argVals = evalNArgs(PRIM_NAME, etor, args, {TypeId::Z_ANY});
            Object* arg = argVals->first();
            std::ostringstream oss;
            oss << arg;
            String* string = new String(oss.str());
            return string;
        }

    }
}
