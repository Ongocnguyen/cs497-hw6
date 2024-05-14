#include <plx/literal/PrimitiveFunction.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/prim/Array.hpp>
#include <plx/prim/Data.hpp>
#include <plx/prim/Global.hpp>
#include <plx/prim/HashTable.hpp>
#include <plx/prim/IO.hpp>
#include <plx/prim/List.hpp>
#include <plx/prim/Operator.hpp>
#include <plx/prim/Queue.hpp>

namespace PLX {

    void definePrim(Evaluator* etor, const std::string& name, Primitive prim) {
        etor->bind(Identifier::create(name), new PrimitiveFunction(name, prim));
    }

    void definePrims(Evaluator* etor) {
        // Global
        definePrim(etor, "argMap", Prim_Global::argMap);
        definePrim(etor, "eval", Prim_Global::eval);
        definePrim(etor, "not", Prim_Global::notOperator);
        definePrim(etor, "repl", Prim_Global::repl);
        definePrim(etor, "type", Prim_Global::type);
        // Array
        definePrim(etor, "get", Prim_Array::get);
        definePrim(etor, "set", Prim_Array::set);
        // Data
        definePrim(etor, "length", Prim_Data::length);
        definePrim(etor, "toArray", Prim_Data::toArray);
        definePrim(etor, "toList", Prim_Data::toList);
        definePrim(etor, "toQueue", Prim_Data::toQueue);
        definePrim(etor, "toString", Prim_Data::toString);
        // HashTable
        definePrim(etor, "keys", Prim_HashTable::keys);
        // IO
        definePrim(etor, "display", Prim_IO::display);
        definePrim(etor, "nl", Prim_IO::nl);
        definePrim(etor, "readLine", Prim_IO::readLine);
        definePrim(etor, "show", Prim_IO::show);
        // List
        definePrim(etor, "first", Prim_List::first);
        definePrim(etor, "rest", Prim_List::rest);
        // Queue
        definePrim(etor, "enq", Prim_Queue::enq);
        definePrim(etor, "deq", Prim_Queue::deq);
        // Operator
        definePrim(etor, "=", Prim_Operator::bind);
        definePrim(etor, "==", Prim_Operator::equalTo);
        definePrim(etor, "+", Prim_Operator::plus);
        definePrim(etor, "-", Prim_Operator::minus);
        definePrim(etor, "*", Prim_Operator::times);
        definePrim(etor, "/", Prim_Operator::divide);
        definePrim(etor, ".", Prim_Operator::dot);
        definePrim(etor, "%", Prim_Operator::percent);
    }

}
