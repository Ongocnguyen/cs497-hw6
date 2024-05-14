#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/BinOpExpr.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/String.hpp>

namespace PLX {

    class BinOpExpr_Test : public PlxTestFixture {};

    TEST_F(BinOpExpr_Test, CreateInstance) {
        Integer* i100 = new Integer(100);
        Identifier* plus = Identifier::create("+");
        Integer* i200 = new Integer(200);
        BinOpExpr* binOpExpr = new BinOpExpr(i100, plus, i200);
        EXPECT_TRUE(binOpExpr->isA(TypeId::E_BINOPEXPR));
        EXPECT_EQ("BinOp", binOpExpr->typeName());
    }

    TEST_F(BinOpExpr_Test, Eval) {
        Integer* i100 = new Integer(100);
        Identifier* plus = Identifier::create("+");
        Integer* i200 = new Integer(200);
        BinOpExpr* binOpExpr = new BinOpExpr(i100, plus, i200);
        Evaluator* etor = new Evaluator();
        Object* result = binOpExpr->eval(etor);
        Integer* expectedResult = new Integer(300);
        EXPECT_EQ(*expectedResult, *result);
    }

    TEST_F(BinOpExpr_Test, MarkChildren) {
        Integer* i100 = new Integer(100);
        Identifier* plus = Identifier::create("+");
        Integer* i200 = new Integer(200);
        BinOpExpr* binOpExpr = new BinOpExpr(i100, plus, i200);
        EXPECT_FALSE(binOpExpr->isMarked());
        EXPECT_FALSE(i100->isMarked());
        EXPECT_FALSE(plus->isMarked());
        EXPECT_FALSE(i200->isMarked());
        binOpExpr->markChildren();
        EXPECT_FALSE(binOpExpr->isMarked());
        EXPECT_TRUE(i100->isMarked());
        EXPECT_TRUE(plus->isMarked());
        EXPECT_TRUE(i200->isMarked());
    }

    TEST_F(BinOpExpr_Test, ShowOn) {
        Integer* i100 = new Integer(100);
        Identifier* plus = Identifier::create("+");
        Integer* i200 = new Integer(200);
        BinOpExpr* binOpExpr = new BinOpExpr(i100, plus, i200);
        std::stringstream ss;
        ss << binOpExpr;
        EXPECT_EQ("100 + 200", ss.str());
    }

}
