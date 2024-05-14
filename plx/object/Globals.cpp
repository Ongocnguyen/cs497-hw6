#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Function.hpp>
#include <plx/literal/Boolean.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    Globals* GLOBALS;

    Globals::Globals() {
    }

    Globals::~Globals() {
    }

    void Globals::initializeAll() {
        // Permanent objects -----------------------------------------------
        _nil = new Nil();
        _true = new Boolean(true);
        _false = new Boolean(false);
        _emptyList = new List();
        _emptyTriple = new Triple();
        _emptyFunction = new Function();  // depends on _nil and _emptyList
        _dynamicEnvironment = new Triple();

        // Root objects ----------------------------------------------------
        _identifierInternTable = new HashTable();
        _symbolInternTable = new HashTable();
        _argMap = new HashTable();

        // Regular objects -------------------------------------------------
        _booleanSymbol = Symbol::create("Boolean");
        _eoiSymbol = Symbol::create("EOI");
        _identifierSymbol = Symbol::create("Identifier");
        _integerSymbol = Symbol::create("Integer");
        _nilSymbol = Symbol::create("Nil");
        _parseIgnoreSymbol = Symbol::create("__PARSE_IGNORE_SYMBOL__");
        _reservedSymbol = Symbol::create("Reserved");
        _specialSymbol = Symbol::create("Special");
        _stringSymbol = Symbol::create("String");
        _symbolSymbol = Symbol::create("Symbol");

        // Other initialization --------------------------------------------

    }

    // Functions that return instances of things ---------------------------

    GC*        Globals::Gc() { return _gc; }
    Function*  Globals::EmptyFunction() { return _emptyFunction; }
    List*      Globals::EmptyList() { return _emptyList; }
    Triple*    Globals::EmptyTriple() { return _emptyTriple; }
    Boolean*   Globals::True() { return _true; }
    Boolean*   Globals::False() { return _false; }
    Nil*       Globals::NilObject() { return _nil; }
    HashTable* Globals::SymbolInternTable() { return _symbolInternTable; }
    HashTable* Globals::IdentifierInternTable() { return _symbolInternTable; }
    void       Globals::SetArgMap(HashTable* argMap) { _argMap = argMap; }
    HashTable* Globals::ArgMap() { return _argMap; }
    Triple*    Globals::DynamicEnvironment() { return _dynamicEnvironment; }
    ReadEvalPrint* Globals::TheReadEvalPrint() { return _readEvalPrint; }

    Symbol*    Globals::BooleanSymbol() { return _booleanSymbol; }
    Symbol*    Globals::EoiSymbol() { return _eoiSymbol; }
    Symbol*    Globals::IdentifierSymbol() { return _identifierSymbol; }
    Symbol*    Globals::IntegerSymbol() { return _integerSymbol; }
    Symbol*    Globals::NilSymbol() { return _nilSymbol; }
    Symbol*    Globals::ParseIgnoreSymbol() { return _parseIgnoreSymbol; }
    Symbol*    Globals::ReservedSymbol() { return _reservedSymbol; }
    Symbol*    Globals::SpecialSymbol() { return _specialSymbol; }
    Symbol*    Globals::StringSymbol() { return _stringSymbol; }
    Symbol*    Globals::SymbolSymbol() { return _symbolSymbol; }

}
