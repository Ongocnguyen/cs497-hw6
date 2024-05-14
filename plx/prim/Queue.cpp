#include <cassert>

#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>
#include <plx/prim/Primitive.hpp>

namespace PLX {
    namespace Prim_Queue {

        Object* enq(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("enq", etor, args, {TypeId::D_QUEUE, TypeId::Z_ANY});
            Queue* queue = static_cast<Queue*>(argVals->first());
            Object* elem = argVals->second();
            queue->enq(elem);
            return queue;
        }

        Object* deq(Evaluator* etor, List* args) {
            List* argVals = evalNArgs("deq", etor, args, {TypeId::D_QUEUE});
            Queue* queue = static_cast<Queue*>(argVals->first());
            return queue->deq();
        }

    }
}
