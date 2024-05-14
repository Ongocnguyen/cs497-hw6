#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/String.hpp>

namespace PLX {

    Identifier* Identifier::create(const std::string& name) {
        String* stringName = new String(name);
        HashCode hashCode;
        stringName->hashCode(hashCode);
        Object* identifierObj;
        Identifier* identifier;
        HashTable* internTable = GLOBALS->IdentifierInternTable();
        if (internTable->get(stringName, identifierObj)) {
            identifier = static_cast<Identifier*>(identifierObj);
        }
        else {
            identifier = new Identifier(name);
            internTable->put(stringName, identifier);
        }
        return identifier;
    }

    Identifier::Identifier(const std::string& name)
        : Symbolic(name, TypeId::E_IDENTIFIER)
    {}

    Object* Identifier::eval(Evaluator* etor) {
        return etor->lookup(this);
    }

    List* Identifier::freeVars(List* freeVars) {
        return new List(this, freeVars);
    }

    bool Identifier::match(Object* other, Triple*& bindings) {
        bindings = new Triple(this, other, bindings);
        return true;
    }

    TypeId Identifier::typeId() const {
        return TypeId::E_IDENTIFIER;
    }

}
