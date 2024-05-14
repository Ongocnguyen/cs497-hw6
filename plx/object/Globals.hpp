#pragma once

namespace PLX {

    class GC;
    class Globals;
    class HashTable;
    class List;
    class Triple;
    class Function;
    class Boolean;
    class Nil;
    class Symbol;
    class P_Data;
    class P_Literal;
    class ReadEvalPrint;

    extern Globals* GLOBALS;

    class Globals {
    public:
        Globals();
        ~Globals();

        void initializeAll();

        // The function names are capitalized because otherwise some of the
        // names collide with intrinsic C++ names (like true and false).
        GC* Gc();
        HashTable* IdentifierInternTable();
        HashTable* SymbolInternTable();
        void SetArgMap(HashTable* argMap);
        HashTable* ArgMap();
        Triple* EmptyTriple();
        List* EmptyList();
        Function* EmptyFunction();
        Boolean* True();
        Boolean* False();
        Nil* NilObject();
        Triple* DynamicEnvironment();
        ReadEvalPrint* TheReadEvalPrint();
        Symbol* BooleanSymbol();
        Symbol* EoiSymbol();
        Symbol* IdentifierSymbol();
        Symbol* IntegerSymbol();
        Symbol* NilSymbol();
        Symbol* ParseIgnoreSymbol();
        Symbol* ReservedSymbol();
        Symbol* SpecialSymbol();
        Symbol* StringSymbol();
        Symbol* SymbolSymbol();

    private:
        GC* _gc {nullptr};
        HashTable* _identifierInternTable {nullptr};
        HashTable* _symbolInternTable {nullptr};
        HashTable* _argMap {nullptr};
        List* _emptyList {nullptr};
        Triple* _emptyTriple {nullptr};
        Function* _emptyFunction {nullptr};
        Nil* _nil {nullptr};
        Triple* _dynamicEnvironment {nullptr};
        ReadEvalPrint* _readEvalPrint {nullptr};
        Boolean* _true {nullptr};
        Boolean* _false {nullptr};
        Symbol* _booleanSymbol {nullptr};
        Symbol* _eoiSymbol {nullptr};
        Symbol* _identifierSymbol {nullptr};
        Symbol* _integerSymbol {nullptr};
        Symbol* _nilSymbol {nullptr};
        Symbol* _parseIgnoreSymbol {nullptr};
        Symbol* _reservedSymbol {nullptr};
        Symbol* _specialSymbol {nullptr};
        Symbol* _stringSymbol {nullptr};
        Symbol* _symbolSymbol {nullptr};
        // P_Data* _pData {nullptr};
        // P_Literal* _pLiteral {nullptr};
    };

}
