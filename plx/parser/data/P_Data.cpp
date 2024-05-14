#include <plx/parser/data/P_Data.hpp>
#include <plx/parser/P_Primitive.hpp>

namespace PLX {

    bool pData(List*& tokens, Object*& value) {
        static const std::initializer_list<Parser> parserList {
            pArray,
            pBinding,
            pList,
            pQueue,
            pHashTable
        };
        return pOneOf(parserList, tokens, value);
    }

    bool pDataWithoutBinding(List*& tokens, Object*& value) {
        static const std::initializer_list<Parser> parserList {
            pArray,
            pList,
            pQueue,
            pHashTable
        };
        return pOneOf(parserList, tokens, value);
    }

}
