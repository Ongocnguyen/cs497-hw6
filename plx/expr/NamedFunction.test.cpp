#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Closure.hpp>
#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Function.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/expr/NamedFunction.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>

namespace PLX {

    class NamedFunction_Test : public PlxTestFixture {};

    TEST_F(NamedFunction_Test, CreateInstance) {
        List* parameters = GLOBALS->EmptyList();
        Object* body = GLOBALS->NilObject();
        Function* fun1 = new Function(parameters, body);
        Identifier* name = Identifier::create("foo");
        NamedFunction* namedFun1 = new NamedFunction(name, fun1);
        EXPECT_TRUE(namedFun1->isA(TypeId::E_NAMEDFUNCTION));
        EXPECT_EQ("Function", namedFun1->typeName());
    }

    TEST_F(NamedFunction_Test, Eval_Evaluator) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        List* parameters = new List(x);
        Object* body = new Array({x, y});
        Function* fun1 = new Function(parameters, body);
        Identifier* name = Identifier::create("foo");
        NamedFunction* namedFun1 = new NamedFunction(name, fun1);
        Evaluator* etor = new Evaluator();
        Object* value1 = etor->evalExpr(namedFun1);
        ASSERT_EQ(GLOBALS->NilObject(), value1);
        Object* value2 = etor->lookup(name);
        std::stringstream ss;
        ss << value2;
        EXPECT_EQ("fun (x) = {x, y}", ss.str());
    }

    TEST_F(NamedFunction_Test, MarkChildren) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        List* parameters = new List(x);
        Object* body = new Array({x, y});
        Function* fun1 = new Function(parameters, body);
        Identifier* name = Identifier::create("foo");
        NamedFunction* namedFun1 = new NamedFunction(name, fun1);
        EXPECT_FALSE(namedFun1->isMarked());
        EXPECT_FALSE(name->isMarked());
        EXPECT_FALSE(fun1->isMarked());
        namedFun1->markChildren();
        EXPECT_FALSE(namedFun1->isMarked());
        EXPECT_TRUE(name->isMarked());
        EXPECT_TRUE(fun1->isMarked());
    }

    TEST_F(NamedFunction_Test, ShowOn) {
        Identifier* x = Identifier::create("x");
        Identifier* y = Identifier::create("y");
        List* parameters = new List(x);
        Object* body = new Array({x, y});
        Function* fun1 = new Function(parameters, body);
        Identifier* name = Identifier::create("foo");
        NamedFunction* namedFun1 = new NamedFunction(name, fun1);
        std::stringstream ss;
        ss << namedFun1;
        EXPECT_EQ("fun foo(x) = {x, y}", ss.str());
    }

}
