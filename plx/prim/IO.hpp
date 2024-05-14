namespace PLX {

    class Evaluator;
    class List;
    class Object;

    namespace Prim_IO {

        Object* display(Evaluator* etor, List* args);
        Object* nl(Evaluator* etor, List* args);
        Object* readLine(Evaluator* etor, List* args);
        Object* show(Evaluator* etor, List* args);

    }
}
