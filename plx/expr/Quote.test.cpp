#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/Quote.hpp>
#include <plx/literal/Nil.hpp>

namespace PLX {

    class Quote_Test : public PlxTestFixture {};

    TEST_F(Quote_Test, CreateInstance) {
        Quote* quote1 = new Quote(GLOBALS->NilObject());
        EXPECT_TRUE(quote1->isA(TypeId::E_QUOTE));
        EXPECT_EQ("Quote", quote1->typeName());
    }

    TEST_F(Quote_Test, Eval_Evaluator) {
        Evaluator* etor = new Evaluator();
        Identifier* x = Identifier::create("x");
        Quote* quote = new Quote(x);
        Object* resObj = etor->evalExpr(quote);
        EXPECT_EQ(x, resObj);
    }

    TEST_F(Quote_Test, MarkChildren) {
        Identifier* x = Identifier::create("x");
        Quote* quote = new Quote(x);
        EXPECT_FALSE(quote->isMarked());
        EXPECT_FALSE(x->isMarked());
        quote->markChildren();
        EXPECT_FALSE(quote->isMarked());
        EXPECT_TRUE(x->isMarked());
    }

    TEST_F(Quote_Test, ShowOn) {
        std::stringstream ss;
        Identifier* x = Identifier::create("x");
        Quote* quote = new Quote(x);
        ss << quote;
        EXPECT_EQ("'x'", ss.str());
    }

}
