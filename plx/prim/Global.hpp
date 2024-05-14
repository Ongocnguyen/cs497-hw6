namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_Global {

        Object* argMap(Evaluator* etor, List* args);
        Object* eval(Evaluator* etor, List* args);
        Object* notOperator(Evaluator* etor, List* args);
        Object* repl(Evaluator* etor, List* args);
        Object* tokenize(Evaluator* etor, List* args);
        Object* type(Evaluator* etor, List* args);

    }
}
