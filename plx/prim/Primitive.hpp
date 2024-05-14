#include <list>
#include <string>

#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Evaluator;
    class List;

    void argumentCountMismatch(const std::string& name, int nExpectedArgs, int nActualArgs);

    List* evalArgs(Evaluator* etor, List* args);
    List* evalNArgs(const std::string& name, Evaluator* etor, List* args, std::initializer_list<TypeId> types);

}
