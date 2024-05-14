#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Throw.hpp>
#include <plx/expr/TryCatch.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class TryCatch_Test : public PlxTestFixture {};

    TEST_F(TryCatch_Test, CreateInstance) {
        Integer* i10 = new Integer(10);
        TryCatch* tryCatch = new TryCatch(i10, GLOBALS->EmptyTriple());
        EXPECT_TRUE(tryCatch->isA(TypeId::E_TRYCATCH));
        EXPECT_EQ("TryCatch", tryCatch->typeName());
    }

    TEST_F(TryCatch_Test, Eval_NoThrow) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        TryCatch* tryCatch = new TryCatch(i10, GLOBALS->EmptyTriple());
        Object* value;
        ASSERT_NO_THROW(value = etor->evalExpr(tryCatch));
        EXPECT_EQ(i10, value);
    }

    TEST_F(TryCatch_Test, Eval_ThrowNoCatch) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        Throw* throwExpr = new Throw(i10);
        TryCatch* tryCatch = new TryCatch(throwExpr, GLOBALS->EmptyTriple());
        EXPECT_THROW(etor->evalExpr(tryCatch), Object*);
    }

    TEST_F(TryCatch_Test, Eval_ThrowCatch1) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        Integer* i100 = new Integer(100);
        Throw* throwExpr = new Throw(i10);
        Triple* rules = new Triple(i10, i100);
        TryCatch* tryCatch = new TryCatch(throwExpr, rules);
        Object* value;
        ASSERT_NO_THROW(value = etor->evalExpr(tryCatch));
        EXPECT_EQ(i100, value);
    }

    TEST_F(TryCatch_Test, Eval_ThrowCatch2) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        Integer* i20 = new Integer(20);
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Throw* throwExpr = new Throw(i20);
        Triple* rules = new Triple(i10, i100, new Triple(i20, i200));
        TryCatch* tryCatch = new TryCatch(throwExpr, rules);
        Object* value;
        ASSERT_NO_THROW(value = etor->evalExpr(tryCatch));
        EXPECT_EQ(i200, value);
    }

    class StateChanger : public Object {
    public:
        Object* eval(Evaluator* etor) override {
            (void)etor;
            state++;
            return this;
        }
        int state = 0;
    };

    TEST_F(TryCatch_Test, Eval_NoThrowFinally) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        StateChanger* stateChanger = new StateChanger();
        TryCatch* tryCatch = new TryCatch(i10, GLOBALS->EmptyTriple(), stateChanger);
        Object* value;
        ASSERT_NO_THROW(value = etor->evalExpr(tryCatch));
        EXPECT_EQ(i10, value);
        EXPECT_EQ(1, stateChanger->state);
    }

    TEST_F(TryCatch_Test, Eval_ThrowCatchFinally) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        Integer* i100 = new Integer(100);
        Throw* throwExpr = new Throw(i10);
        Triple* rules = new Triple(i10, i100);
        StateChanger* stateChanger = new StateChanger();
        TryCatch* tryCatch = new TryCatch(throwExpr, rules, stateChanger);
        Object* value;
        ASSERT_NO_THROW(value = etor->evalExpr(tryCatch));
        EXPECT_EQ(i100, value);
        EXPECT_EQ(1, stateChanger->state);
    }

    TEST_F(TryCatch_Test, Eval_ThrowNoCatchFinally) {
        Evaluator* etor = new Evaluator();
        Integer* i10 = new Integer(10);
        Throw* throwExpr = new Throw(i10);
        StateChanger* stateChanger = new StateChanger();
        TryCatch* tryCatch = new TryCatch(throwExpr, GLOBALS->EmptyTriple(), stateChanger);
        ASSERT_THROW(etor->evalExpr(tryCatch), Object*);
        EXPECT_EQ(1, stateChanger->state);
    }

    TEST_F(TryCatch_Test, MarkChildren) {
        Integer* i10 = new Integer(10);
        Integer* i100 = new Integer(100);
        String* finally = new String("finally");
        Throw* throwExpr = new Throw(i10);
        Triple* rules = new Triple(i10, i100);
        TryCatch* tryCatch = new TryCatch(throwExpr, rules, finally);
        EXPECT_FALSE(tryCatch->isMarked());
        EXPECT_FALSE(throwExpr->isMarked());
        EXPECT_FALSE(rules->isMarked());
        EXPECT_FALSE(finally->isMarked());
        tryCatch->markChildren();
        EXPECT_FALSE(tryCatch->isMarked());
        EXPECT_TRUE(throwExpr->isMarked());
        EXPECT_TRUE(rules->isMarked());
        EXPECT_TRUE(finally->isMarked());
    }

    TEST_F(TryCatch_Test, ShowOn) {
        Integer* i10 = new Integer(10);
        Integer* i20 = new Integer(20);
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Throw* throwExpr = new Throw(i10);
        Triple* rules = new Triple(i10, i100, new Triple(i20, i200));
        TryCatch* tryCatch = new TryCatch(throwExpr, rules, i300);
        std::stringstream ss;
        ss << tryCatch;
        EXPECT_EQ("try throw 10 catch 10=100 | 20=200 finally 300 end", ss.str());
    }

}