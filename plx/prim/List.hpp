
namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_List {

        Object* asArray(Evaluator* etor, List* args);
        Object* first(Evaluator* etor, List* args);
        Object* rest(Evaluator* etor, List* args);
        Object* setFirst(Evaluator* etor, List* args);
        Object* setRest(Evaluator* etor, List* args);

    }
}
