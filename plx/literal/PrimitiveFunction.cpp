#include <plx/literal/PrimitiveFunction.hpp>

namespace PLX {

    PrimitiveFunction::PrimitiveFunction(const std::string& name, Primitive primitive)
        : _name {name}
        , _primitive {primitive}
    {}

    Object* PrimitiveFunction::apply(Evaluator* etor, List* arguments) {
        return _primitive(etor, arguments);
    }

    bool PrimitiveFunction::hashCode(HashCode& hashCode) {
        static const int typeHashCode = std::hash<int>{}(static_cast<int>(typeId()));
        static const std::hash<Primitive> primHasher;
        hashCode = typeHashCode ^ (primHasher(_primitive) << 1);
        return true;
    }

    std::string PrimitiveFunction::name() {
        return _name;
    }

    void PrimitiveFunction::showOn(std::ostream& ostream) const {
        ostream << typeName()
                << '{' << _name << '@'
                << reinterpret_cast<void*>(_primitive)
                << '}';
    }

    TypeId PrimitiveFunction::typeId() const {
        return TypeId::L_PRIMITIVEFUNCTION;
    }

}
