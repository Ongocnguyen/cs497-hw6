#include <plx/data/HashTable.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    extern bool hashDebug;

    Symbol* Symbol::create(const std::string& name) {
        String* stringName = new String(name);
        Object* symbolObj;
        Symbol* symbol;
        HashTable* internTable = GLOBALS->SymbolInternTable();
        if (internTable->get(stringName, symbolObj)) {
            symbol = static_cast<Symbol*>(symbolObj);
        }
        else {
            symbol = new Symbol(name);
            internTable->put(stringName, symbol);
        }
        return symbol;
    }

    Symbol::Symbol(const std::string& name)
        : Symbolic(name, TypeId::L_SYMBOL)
    {}

    TypeId Symbol::typeId() const {
        return TypeId::L_SYMBOL;
    }

}
