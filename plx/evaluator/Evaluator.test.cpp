#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Evaluator_Test : public PlxTestFixture {
    public:
        Evaluator_Test()
            : _etor {new Evaluator()}
        {}
        Evaluator* _etor;
    };

    class EvaluatorTestObject : public Object {
    public:
        EvaluatorTestObject()
            : evalCalled {0}
        {}

        Object* eval(Evaluator* etor) override {
            evalCalled++;
            env = etor->environment();
            return this;
        }

        int evalCalled;
        Triple* env;
    };

    TEST_F(Evaluator_Test, CreateInstance) {
        EXPECT_TRUE(_etor->isA(TypeId::T_EVALUATOR));
        EXPECT_EQ("Evaluator", _etor->typeName());
    }

    TEST_F(Evaluator_Test, BindAndLookup) {
        Identifier* key1 = Identifier::create("abc");
        Integer* value1 = new Integer(100);
        _etor->bind(key1, value1);
        Object* value = _etor->lookup(key1);
        EXPECT_EQ(value1, value);
        Identifier* key2 = Identifier::create("def");
        EXPECT_THROW(_etor->lookup(key2), Array*);
    }

    TEST_F(Evaluator_Test, Eval) {
        EvaluatorTestObject* testObject = new EvaluatorTestObject();
        Object* value = _etor->evalExpr(testObject);
        EXPECT_EQ(testObject, value);
        EXPECT_EQ(1, testObject->evalCalled);
    }

    TEST_F(Evaluator_Test, EvalWithEnv) {
        EvaluatorTestObject* testObject = new EvaluatorTestObject();
        Triple* env1 = new Triple();
        Object* value = _etor->evalExpr(testObject, env1);
        EXPECT_EQ(testObject, value);
        EXPECT_EQ(1, testObject->evalCalled);
        EXPECT_EQ(env1, testObject->env);
    }

    TEST_F(Evaluator_Test, MarkChildren) {
        String* key = new String("abc");
        Integer* value = new Integer(100);
        _etor->bind(key, value);
        EXPECT_FALSE(_etor->isMarked());
        EXPECT_FALSE(key->isMarked());
        EXPECT_FALSE(value->isMarked());
        _etor->markChildren();
        EXPECT_FALSE(_etor->isMarked());
        EXPECT_TRUE(key->isMarked());
        EXPECT_TRUE(value->isMarked());
    }

    TEST_F(Evaluator_Test, SetEnvironment) {
        Triple* env = new Triple(Identifier::create("x"), new Integer(100));
        _etor->setEnvironment(env);
        EXPECT_EQ(env, _etor->environment());
    }

}
