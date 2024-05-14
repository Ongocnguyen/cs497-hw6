#include <list>
#include <sstream>

#include <plx/data/Array.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/ThrowException.hpp>

namespace PLX {

    std::ostream& operator<<(std::ostream& ostream, const PLX::Object* object) {
        object->showOn(ostream);
        return ostream;
    }

    bool Object::operator==(const Object& rhs) const {
        return this->equals(&rhs);
    }

    bool Object::operator==(const Object* rhs) const {
        return this->equals(rhs);
    }

    bool Object::operator!=(const Object& rhs) const {
        return !this->equals(&rhs);
    }

    Object::Object() {
    }

    Object* Object::apply(Evaluator* etor, List* arguments) {
        (void)etor;
        (void)arguments;
        throwException("Object::apply", "Object is not applyable", this);
        // This function won't ever return anything, but by putting a
        // return statement here it prevents a compiler warning.
        return this;
    }

    bool Object::boolValue() const {
        return true;
    }

    void Object::displayOn(std::ostream& ostream) const {
        showOn(ostream);
    }

    bool Object::equals(const Object* other) const {
        // The pointers must be cast to void* in case the == operator is
        // ever in the future overloaded to handle Object*.
        const void* thisPtr = static_cast<const void*>(this);
        const void* otherPtr = static_cast<const void*>(other);
        return thisPtr == otherPtr;
    }

    Object* Object::eval(Evaluator* etor) {
        (void)etor;
        // by default an object evaluates to itself
        return this;
    }

    List* Object::freeVars(List* freeVars) {
        return freeVars;
    }

    List* Object::freeVars(std::initializer_list<Object*> objs, List* freeVars) {
        for (Object* obj : objs) {
            freeVars = obj->freeVars(freeVars);
        }
        return freeVars;
    }

    bool Object::hashCode(HashCode& hashCode) {
        (void)hashCode;
        // void throwException(const std::string& category, const std::string& message, Object* payload);
        Array* payload = new Array({this, this->typeSymbol()});
        throwException("Object", "Object is not hashable", payload);
        return false;
    }

    bool Object::index(Object* indexer, Object*& retrievedValue) {
        (void)indexer;
        (void)retrievedValue;
        return false;
    }

    bool Object::isA(TypeId typeId) const {
        return (this->typeId()) == typeId;
    }

    bool Object::isMarked() const {
        return _isMarked;
    }

    bool Object::length(int& len) {
        (void)len;
        return false;
    }

    void Object::mark() {
        if (!_isMarked) {
            _isMarked = true;
            markChildren();
        }
    }

    bool Object::match(Object* other, Triple*& bindings) {
        (void)bindings;
        return this->equals(other);
    }

    void Object::markChildren() {}

    bool Object::plus(Object* other, Object*& value) {
        (void)other;
        (void)value;
        return false;
    }

    bool Object::minus(Object* other, Object*& value) {
        (void)other;
        (void)value;
        return false;
    }

    bool Object::times(Object* other, Object*& value) {
        (void)other;
        (void)value;
        return false;
    }

    bool Object::divide(Object* other, Object*& value) {
        (void)other;
        (void)value;
        return false;
    }

    bool Object::percent(Object* other, Object*& value) {
        (void)other;
        (void)value;
        return false;
    }

    void Object::showOn(std::ostream& ostream) const {
        ostream << "Object@" << static_cast<const void*>(this);
    }

    bool Object::toArray(Array*& array) {
        (void)array;
        return false;
    }

    bool Object::toList(List*& list) {
        (void)list;
        return false;
    }

    bool Object::toQueue(Queue*& queue) {
        (void)queue;
        return false;
    }

    std::string Object::toString() {
        std::ostringstream ss;
        ss << this;
        return ss.str();
    }

    TypeId Object::typeId() const {
        return TypeId::T_OBJECT;
    }

    std::string Object::typeName() const {
        // return "Object";
        return TYPE_NAMES[typeId()];
    }

    Symbol* Object::typeSymbol() const {
        return Symbol::create(typeName());
    }

    void Object::unmark() {
        _isMarked = false;
    }

}
