#include <cassert>

#include <plx/parser/expr/P_Expr.hpp>
#include <plx/parser/P_Primitive.hpp>

namespace PLX {

    bool pExpr(List*& tokens, Object*& value) {
        static const std::initializer_list<Parser> parserList {
            // pBinOpExpr,
            pApply,
            pDo,
            pFunction,
            pIdentifier,
            pIf,
            pLet,
            pMatch,
            pParenExpr,
            pQuote,
            pThrow,
            pTryCatch
        };
        return pOneOf(parserList, tokens, value);
    }

}
