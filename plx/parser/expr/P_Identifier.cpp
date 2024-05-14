#include <plx/object/Globals.hpp>
#include <plx/parser/P_Primitive.hpp>

namespace PLX {

    bool pIdentifier(List*& tokens, Object*& value) {
        return pSpotAndStrip(GLOBALS->IdentifierSymbol(), tokens, value);
    }

}