namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_Operator {

        Object* bind(Evaluator* etor, List* args);
        Object* divide(Evaluator* etor, List* args);
        Object* dot(Evaluator* etor, List* args);
        Object* equalTo(Evaluator* etor, List* args);
        Object* minus(Evaluator* etor, List* args);
        Object* plus(Evaluator* etor, List* args);
        Object* times(Evaluator* etor, List* args);
        Object* percent(Evaluator* etor, List* args);

    }
}
