# to build:
# $ cmake -H. -Bbuild  # one time only
# $ cmake --build build

cmake_minimum_required(VERSION 3.22)

#-----------------------------------------------------------------------
# Project configuration
#-----------------------------------------------------------------------

set(PROJECT_NAME plx)
set(VERSION 0.1.0)
set(DESCRIPTION "Custom programming language for WSU CS497")
set(URL "http://github.com")
set(AUTHOR "Jeff Meunier")

#-----------------------------------------------------------------------
# Compiler configuration
#-----------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-14")  # requires '-gdwarf-4' compiler option
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(${PROJECT_NAME}
        VERSION      ${VERSION}
        DESCRIPTION  ${DESCRIPTION}
        HOMEPAGE_URL ${URL}
        LANGUAGES    CXX)  # where CXX == C++

message("compile options: " ${COMPILE_OPTIONS})
include_directories("${CMAKE_CURRENT_LIST_DIR}")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_KEEP_TEST_OUTPUTS ON)

# add_compile_options(-O0 -g -ggdb -Wall -Wextra -pedantic -Wswitch-enum -Werror -std=c++14)
add_compile_options(-O0 -g -ggdb -Wall -Wextra -pedantic -Werror -std=c++14 -gdwarf-4)

#-----------------------------------------------------------------------
# Source files
#-----------------------------------------------------------------------

set(EXEC_SRC_FILES
    plx/main.cpp
)

set(LIB_SRC_FILES
    plx/data/Array.cpp
    plx/data/Closure.cpp
    plx/data/HashTable.cpp
    plx/data/List.cpp
    plx/data/Method.cpp
    plx/data/Queue.cpp
    plx/data/Triple.cpp
    plx/evaluator/Evaluator.cpp
    plx/expr/Apply.cpp
    plx/expr/BinOpExpr.cpp
    plx/expr/Do.cpp
    plx/expr/Function.cpp
    plx/expr/Identifier.cpp
    plx/expr/If.cpp
    plx/expr/IndexOp.cpp
    plx/expr/Let.cpp
    plx/expr/LetIn.cpp
    plx/expr/Match.cpp
    plx/expr/NamedFunction.cpp
    plx/expr/ParenExpr.cpp
    plx/expr/Quote.cpp
    plx/expr/Throw.cpp
    plx/expr/TryCatch.cpp
    plx/lexer/Lexer.cpp
    plx/lexer/Syntax.cpp
    plx/literal/Boolean.cpp
    plx/literal/InputStream.cpp
    plx/literal/Integer.cpp
    plx/literal/Nil.cpp
    plx/literal/PrimitiveFunction.cpp
    plx/literal/String.cpp
    plx/literal/Symbol.cpp
    plx/object/Globals.cpp
    plx/object/HashCode.cpp
    plx/object/Object.cpp
    plx/object/Symbolic.cpp
    plx/object/ThrowException.cpp
    plx/object/TypeIds.cpp
    plx/parser/data/P_Array.cpp
    plx/parser/data/P_Binding.cpp
    plx/parser/data/P_Data.cpp
    plx/parser/data/P_HashTable.cpp
    plx/parser/data/P_List.cpp
    plx/parser/data/P_Queue.cpp
    plx/parser/expr/P_Apply.cpp
    plx/parser/expr/P_BinOpExpr.cpp
    plx/parser/expr/P_Do.cpp
    plx/parser/expr/P_Expr.cpp
    plx/parser/expr/P_Function.cpp
    plx/parser/expr/P_Identifier.cpp
    plx/parser/expr/P_If.cpp
    plx/parser/expr/P_Let.cpp
    plx/parser/expr/P_Match.cpp
    plx/parser/expr/P_ParenExpr.cpp
    plx/parser/expr/P_Quote.cpp
    plx/parser/expr/P_Throw.cpp
    plx/parser/expr/P_TryCatch.cpp
    plx/parser/literal/P_Literal.cpp
    plx/parser/P_Any.cpp
    plx/parser/P_Primitive.cpp
    plx/parser/P_ReservedWords.cpp
    plx/parser/P_SpecialChars.cpp
    plx/parser/Parser.cpp
    plx/parser/Parser.cpp
    plx/prim/Array.cpp
    plx/prim/Data.cpp
    plx/prim/DefinePrims.cpp
    plx/prim/Global.cpp
    plx/prim/IO.cpp
    plx/prim/HashTable.cpp
    plx/prim/List.cpp
    plx/prim/Operator.cpp
    plx/prim/Primitive.cpp
    plx/prim/Queue.cpp
)

set(TEST_SRC_FILES
    plx/data/Array.test.cpp
    plx/data/Closure.test.cpp
    plx/data/HashTable.test.cpp
    plx/data/List.test.cpp
    plx/data/Method.test.cpp
    plx/data/Queue.test.cpp
    plx/data/Triple.test.cpp
    plx/evaluator/Evaluator.test.cpp
    plx/expr/Apply.test.cpp
    plx/expr/BinOpExpr.test.cpp
    plx/expr/Do.test.cpp
    plx/expr/Function.test.cpp
    plx/expr/Identifier.test.cpp
    plx/expr/If.test.cpp
    plx/expr/Let.test.cpp
    plx/expr/LetIn.test.cpp
    plx/expr/Match.test.cpp
    plx/expr/NamedFunction.test.cpp
    plx/expr/ParenExpr.test.cpp
    plx/expr/Quote.test.cpp
    plx/expr/Throw.test.cpp
    plx/expr/TryCatch.test.cpp
    plx/lexer/Lexer.test.cpp
    plx/literal/Boolean.test.cpp
    plx/literal/InputStream.test.cpp
    plx/literal/Integer.test.cpp
    plx/literal/Nil.test.cpp
    plx/literal/PrimitiveFunction.test.cpp
    plx/literal/String.test.cpp
    plx/literal/Symbol.test.cpp
    plx/object/Globals.test.cpp
    plx/object/Object.test.cpp
    plx/parser/data/P_Array.test.cpp
    plx/parser/data/P_Binding.test.cpp
    plx/parser/data/P_HashTable.test.cpp
    plx/parser/data/P_List.test.cpp
    plx/parser/data/P_Queue.test.cpp
    plx/parser/expr/P_Apply.test.cpp
    plx/parser/expr/P_BinOpExpr.test.cpp
    plx/parser/expr/P_Do.test.cpp
    plx/parser/expr/P_Function.test.cpp
    plx/parser/expr/P_Identifier.test.cpp
    plx/parser/expr/P_If.test.cpp
    plx/parser/expr/P_Let.test.cpp
    plx/parser/expr/P_Match.test.cpp
    plx/parser/expr/P_ParenExpr.test.cpp
    plx/parser/expr/P_Quote.test.cpp
    plx/parser/expr/P_Throw.test.cpp
    plx/parser/expr/P_TryCatch.test.cpp
    plx/parser/literal/P_Literal.test.cpp
    plx/parser/P_Any.test.cpp
    plx/parser/P_Primitive.test.cpp
    plx/parser/Parser.test.cpp
    test/PlxTestFixture.cpp
    test/test_main.cpp
    test/TestUtils.cpp
)

# compile all the LIB_SRC_FILES files into a library
add_library(
    ${PROJECT_NAME}_lib
    ${LIB_SRC_FILES}
)

#-----------------------------------------------------------------------
# Main executable
#-----------------------------------------------------------------------

add_executable(
    ${PROJECT_NAME}
    ${EXEC_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_lib
)

#-----------------------------------------------------------------------
# Testing
#-----------------------------------------------------------------------

find_package(GTest REQUIRED)

set(TEST_EXE_NAME ${PROJECT_NAME}-test)

add_executable(
    ${TEST_EXE_NAME}
    ${TEST_SRC_FILES}
)

target_link_libraries(
    ${TEST_EXE_NAME}
    ${PROJECT_NAME}_lib
    GTest::GTest
)
