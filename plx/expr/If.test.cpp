#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/If.hpp>
#include <plx/literal/Boolean.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    class If_Test : public PlxTestFixture {};

    TEST_F(If_Test, CreateInstance) {
        If* if1 = new If(GLOBALS->True(), GLOBALS->NilObject(), GLOBALS->NilObject());
        EXPECT_TRUE(if1->isA(TypeId::E_IF));
        EXPECT_EQ("IfThen", if1->typeName());
    }

    TEST_F(If_Test, Eval_True_Evaluator) {
        Evaluator* etor = new Evaluator();
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        If* if1 = new If(GLOBALS->True(), i100, i200);
        Object* resObj = etor->evalExpr(if1);
        EXPECT_EQ(i100, resObj);
    }

    TEST_F(If_Test, Eval_False_Evaluator) {
        Evaluator* etor = new Evaluator();
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        If* if1 = new If(GLOBALS->False(), i100, i200);
        Object* resObj = etor->evalExpr(if1);
        EXPECT_EQ(i200, resObj);
    }

    TEST_F(If_Test, MarkChildren) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(200);
        If* if1 = new If(i100, i200, i300);
        EXPECT_FALSE(if1->isMarked());
        EXPECT_FALSE(i100->isMarked());
        EXPECT_FALSE(i200->isMarked());
        EXPECT_FALSE(i300->isMarked());
        if1->markChildren();
        EXPECT_FALSE(if1->isMarked());
        EXPECT_TRUE(i100->isMarked());
        EXPECT_TRUE(i200->isMarked());
        EXPECT_TRUE(i300->isMarked());
    }

    TEST_F(If_Test, ShowOn) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        If* if1 = new If(i100, i200, i300);
        std::stringstream ss;
        ss << if1;
        EXPECT_EQ("if 100 then 200 else 300", ss.str());
    }

}