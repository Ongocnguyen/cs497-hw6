#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/List.hpp>
#include <plx/evaluator/Evaluator.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/PrimitiveFunction.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    static List* arguments;

    class PrimitiveFunction_Test : public PlxTestFixture {
    public:
        PrimitiveFunction_Test()
            : PlxTestFixture()
        {
            arguments = GLOBALS->EmptyList();
        }
    };

    Object* prim1(Evaluator* etor, List* arguments) {
        (void)etor;
        PLX::arguments = arguments;
        return GLOBALS->NilObject();
    }

    TEST_F(PrimitiveFunction_Test, CreateInstance) {
        PrimitiveFunction* primFunction = new PrimitiveFunction("prim1", prim1);
        EXPECT_EQ(TypeId::L_PRIMITIVEFUNCTION, primFunction->typeId());
        EXPECT_EQ("PrimitiveFunction", primFunction->typeName());
    }

    TEST_F(PrimitiveFunction_Test, Apply) {
        Evaluator* etor = new Evaluator();
        Integer* i100 = new Integer(100);
        List* args = List::create({i100});
        PrimitiveFunction* primFunction = new PrimitiveFunction("prim1", prim1);
        Object* value = primFunction->apply(etor, args);
        EXPECT_EQ(GLOBALS->NilObject(), value);
        EXPECT_EQ(*args, *arguments);
    }

    TEST_F(PrimitiveFunction_Test, ShowOn) {
        PrimitiveFunction* primFunction = new PrimitiveFunction("prim1", prim1);
        std::stringstream ss;
        ss << primFunction;
        std::string primFunctionString {ss.str()};
        std::string substring {"PrimitiveFunction{" + primFunction->name() + "@"};
        EXPECT_EQ(0, strncmp(primFunctionString.c_str(), substring.c_str(), substring.size()));
    }

}
