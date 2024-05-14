#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/expr/Do.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Do_Test : public PlxTestFixture {};

    class DoTestObject : public Object {
    public:
        DoTestObject() {}
        Object* eval(Evaluator* etor) override {
            (void)etor;
            this->seqValue = DoTestObject::seq++;
            return this;
        }
        int seqValue;
        static int seq;
    };

    int DoTestObject::seq = 0;

    class DoTestObject2 : public Object {
    public:
        DoTestObject2() {}
        Object* eval(Evaluator* etor) override {
            Object* key = new DoTestObject();
            Object* value = new DoTestObject();
            Triple* triple = new Triple(key, value, etor->environment());
            etor->setEnvironment(triple);
            return this;
        }
        int seqValue;
        static int seq;
    };

    TEST_F(Do_Test, CreateInstance) {
        Do* seq = new Do(GLOBALS->EmptyList());
        EXPECT_TRUE(seq->isA(TypeId::E_SEQ));
        EXPECT_EQ("Seq", seq->typeName());
    }

    TEST_F(Do_Test, Eval_Empty_Evaluator) {
        Evaluator* etor = new Evaluator();
        Do* seq = new Do(GLOBALS->EmptyList());
        Object* value = etor->evalExpr(seq);
        EXPECT_EQ(GLOBALS->NilObject(), value);
    }

    TEST_F(Do_Test, Eval_Nonempty_Evaluator) {
        Evaluator* etor = new Evaluator();
        DoTestObject::seq = 0;
        DoTestObject* obj1 = new DoTestObject();
        DoTestObject* obj2 = new DoTestObject();
        DoTestObject* obj3 = new DoTestObject();
        List* seqList =
          new List(obj1,
          new List(obj2,
          new List(obj3)));
        Do* seq = new Do(seqList);
        Object* value = etor->evalExpr(seq);
        EXPECT_EQ(value, obj3);
        EXPECT_EQ(0, obj1->seqValue);
        EXPECT_EQ(1, obj2->seqValue);
        EXPECT_EQ(2, obj3->seqValue);
    }

    TEST_F(Do_Test, Eval_RestoresEnvironment_Evaluator) {
        Evaluator* etor = new Evaluator();
        DoTestObject2* expr = new DoTestObject2();
        Do* seq = new Do(new List(expr));
        Triple* savedEnv = etor->environment();
        etor->evalExpr(seq);
        EXPECT_EQ(savedEnv, etor->environment());
    }

    TEST_F(Do_Test, MarkChildren) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(100);
        Integer* i300 = new Integer(100);
        List* seqList =
          new List(i100,
          new List(i200,
          new List(i300)));
        Do* seq = new Do(seqList);
        EXPECT_FALSE(seq->isMarked());
        EXPECT_FALSE(i100->isMarked());
        EXPECT_FALSE(i200->isMarked());
        EXPECT_FALSE(i300->isMarked());
        seq->markChildren();
        EXPECT_FALSE(seq->isMarked());
        EXPECT_TRUE(i100->isMarked());
        EXPECT_TRUE(i200->isMarked());
        EXPECT_TRUE(i300->isMarked());
    }

    TEST_F(Do_Test, ShowOn) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        List* seqList =
            new List(i100,
            new List(i200,
            new List(i300)));
        Do* seq = new Do(seqList);
        std::stringstream ss;
        ss << seq;
        EXPECT_EQ("do 100 200 300 end", ss.str());
    }

}
