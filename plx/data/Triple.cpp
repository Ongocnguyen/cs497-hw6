#include <cassert>

#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    Triple::Triple()
        : Triple(GLOBALS->NilObject(), GLOBALS->NilObject(), this)
    {}

    Triple::Triple(Object* key, Object* value)
        : Triple(key, value, GLOBALS->EmptyTriple())
    {}

    Triple::Triple(Object* key, Object* value, Triple* next)
        : _key {key}
        , _value {value}
        , _next {next}
    {}

    bool Triple::boolValue() const {
        return this != GLOBALS->EmptyTriple();
    }

    bool Triple::equals(const Object* other) const {
        if (!other->isA(TypeId::D_TRIPLE)) {
            return false;
        }
        const Triple* othertriple = static_cast<const Triple*>(other);
        if (isEmpty()) {
            return othertriple->isEmpty();
        }
        return _key->equals(othertriple->_key) && _value->equals(othertriple->_value);
    }

    Object* Triple::eval(Evaluator* etor) {
        if (isEmpty()) {
            return this;
        }
        Object* keyVal = etor->evalExpr(_key);
        Object* valueVal = etor->evalExpr(_value);
        Object* nextValObj = etor->evalExpr(_next);
        assert(nextValObj->isA(TypeId::D_TRIPLE));
        Triple* nextVal = static_cast<Triple*>(nextValObj);
        return new Triple(keyVal, valueVal, nextVal);
    }

    bool Triple::isEmpty() const {
        return this == GLOBALS->EmptyTriple();
    }

    bool Triple::length(int& len) {
        Triple* triple = this;
        len = 0;
        while (!triple->isEmpty()) {
            len++;
            triple = triple->_next;
        }
        return true;
    }

    Triple* Triple::locate(const Object* key) {
        Triple* triple = this;
        while (!triple->isEmpty()) {
            if (key->equals(triple->_key)) {
                break;
            }
            triple = triple->_next;
        }
        return triple;
    }

    bool Triple::lookup(const Object* key, Object*& value) {
        Triple* binding = locate(key);
        if (binding->isEmpty()) {
            return false;
        }
        value = binding->value();
        return true;
    }

    Object* Triple::key() const {
        return _key;
    }

    Object* Triple::value() const {
        return _value;
    }

    Triple* Triple::next() const {
        return _next;
    }

    void Triple::markChildren() {
        _key->mark();
        _value->mark();
        _next->mark();
    }

    bool Triple::matchLocate(Object* object, Object*& value, Triple*& env) {
        Triple* triple = this;
        while (!triple->isEmpty()) {
            if (triple->key()->match(object, env)) {
                value = triple->value();
                return true;
            }
            triple = triple->next();
        }
        return false; 
    }

    void Triple::setNext(Triple* next) {
        if (isEmpty()) {
            throwException("Triple", "Operation not allowed on empty triple", this);
        }
        _next = next;
    }

    void Triple::setValue(Object* value) {
        if (isEmpty()) {
            throwException("Triple", "Operation not allowed on empty triple", this);
        }
        _value = value;
    }

    void Triple::showOn(std::ostream& ostream) const {
        showOnWith(ostream, ", ");
    }

    void Triple::showOnWith(std::ostream& ostream, const std::string& separator) const {
        bool firstIter = true;
        const Triple* triple = this;
        while (!triple->isEmpty()) {
            if (firstIter) {
                firstIter = false;
            }
            else {
                ostream << separator;
            }
            ostream << triple->_key << '=' << triple->_value;
            triple = triple->_next;
        }
    }

    TypeId Triple::typeId() const {
        return TypeId::D_TRIPLE;
    }

}
