
namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_Data {

        Object* length(Evaluator* etor, List* args);
        Object* toArray(Evaluator* etor, List* args);
        Object* toList(Evaluator* etor, List* args);
        Object* toQueue(Evaluator* etor, List* args);
        Object* toString(Evaluator* etor, List* args);

    }
}
