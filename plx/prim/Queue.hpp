namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_Queue {

        Object* enq(Evaluator* etor, List* args);
        Object* deq(Evaluator* etor, List* args);

    }
}
