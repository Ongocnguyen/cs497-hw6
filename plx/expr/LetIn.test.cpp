#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class LetIn_Test : public PlxTestFixture {};

    TEST_F(LetIn_Test, CreateInstance) {
        LetIn* letIn1 = new LetIn(GLOBALS->EmptyTriple(), GLOBALS->NilObject());
        EXPECT_TRUE(letIn1->isA(TypeId::E_LETIN));
        EXPECT_EQ("LetIn", letIn1->typeName());
    }

    TEST_F(LetIn_Test, Eval_Evaluator) {
        Identifier* x = Identifier::create("x");
        Integer* i100 = new Integer(100);
        LetIn* letIn1 = new LetIn(new Triple(x, i100), x);
        Evaluator* etor = new Evaluator();
        Object* value = etor->evalExpr(letIn1);
        EXPECT_EQ(i100, value);
        EXPECT_THROW(etor->lookup(x), Array*);
    }

    TEST_F(LetIn_Test, Eval_MatchFailure_Evaluator) {
        Evaluator* etor = new Evaluator();
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        LetIn* letIn1 = new LetIn(new Triple(i100, i200), i100);
        EXPECT_THROW(etor->evalExpr(letIn1), Array*);
    }

    TEST_F(LetIn_Test, MarkChildren) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Integer* i100 = new Integer(100);
        LetIn* letIn1 = new LetIn(new Triple(x, i100), y);
        EXPECT_FALSE(letIn1->isMarked());
        EXPECT_FALSE(x->isMarked());
        EXPECT_FALSE(y->isMarked());
        EXPECT_FALSE(i100->isMarked());
        letIn1->markChildren();
        EXPECT_FALSE(letIn1->isMarked());
        EXPECT_TRUE(x->isMarked());
        EXPECT_TRUE(y->isMarked());
        EXPECT_TRUE(i100->isMarked());
    }

    TEST_F(LetIn_Test, ShowOn) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        Identifier* z = Identifier::create("z");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        LetIn* letIn1 = new LetIn(new Triple(x, i100, new Triple(y, i200)), z);
        std::stringstream ss;
        ss << letIn1;
        EXPECT_EQ("let x=100, y=200 in z", ss.str());
    }

}