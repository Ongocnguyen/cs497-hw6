#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Throw.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Throw_Test : public PlxTestFixture {};

    TEST_F(Throw_Test, CreateInstance) {
        Throw* throwExpr = new Throw(GLOBALS->NilObject());
        EXPECT_TRUE(throwExpr->isA(TypeId::E_THROW));
        EXPECT_EQ("Throw", throwExpr->typeName());
    }

    TEST_F(Throw_Test, Eval) {
        Evaluator* etor = new Evaluator();
        Throw* throwExpr = new Throw(GLOBALS->NilObject());
        EXPECT_THROW(etor->evalExpr(throwExpr), Object*);
    }

    TEST_F(Throw_Test, MarkChildren) {
        Integer* i100 = new Integer(100);
        Throw* throwExpr = new Throw(i100);
        EXPECT_FALSE(throwExpr->isMarked());
        EXPECT_FALSE(i100->isMarked());
        throwExpr->markChildren();
        EXPECT_FALSE(throwExpr->isMarked());
        EXPECT_TRUE(i100->isMarked());
    }

    TEST_F(Throw_Test, ShowOn) {
        Integer* i100 = new Integer(100);
        Throw* throwExpr = new Throw(i100);
        std::stringstream ss;
        ss << throwExpr;
        EXPECT_EQ("throw 100", ss.str());
    }

}
