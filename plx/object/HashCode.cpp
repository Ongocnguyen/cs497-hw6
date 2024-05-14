#include <plx/object/HashCode.hpp>

namespace PLX {

    HashCode hashRotateLeft(HashCode n) {
        static const int UINT_HIGH_BIT = static_cast<int>(((unsigned int)-1) / 2 + 1);
        bool g = n >= static_cast<HashCode>(UINT_HIGH_BIT);
        return (n << 1) + g;
    }

}
