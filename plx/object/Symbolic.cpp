#include <plx/object/Symbolic.hpp>

namespace PLX {

    static HashCode _calculateHashCode(const std::string& name, TypeId typeId) {
        static const int typeHashCode = std::hash<int>{}(static_cast<int>(typeId));
        static const std::hash<std::string> stringHasher;
        return typeHashCode ^ (stringHasher(name) << 1);
    }

    Symbolic::Symbolic(const std::string& name, TypeId typeId)
        : _name {name}
        , _hashCode {_calculateHashCode(name, typeId)}
    {}

    bool Symbolic::hashCode(HashCode& hashCode) {
        hashCode = _hashCode;
        return true;
    }

    std::string Symbolic::name() {
        return _name;
    }

    void Symbolic::showOn(std::ostream& ostream) const {
        ostream << _name;
    }

}
