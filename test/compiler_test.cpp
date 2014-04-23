#include "gtest/gtest.h"
#include "compiler.h"

using namespace ECPP;

TEST(Compiler, Empty)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    auto result = c.render(input);

    ASSERT_TRUE(result.first.empty());
    ASSERT_TRUE(result.second.empty());
}

TEST(Compiler, SingleInclude)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("<%i foo.h %>"));

    auto result = c.render(input);

    ASSERT_EQ("#include \"foo.h\"\r\n", result.first);
    ASSERT_TRUE(result.second.empty());
}

TEST(Compiler, MultipleIncludes)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("<%i foo.h %>"));
    input.push_back(Lexer::Instruction::create("<%i bar.h %>"));
    input.push_back(Lexer::Instruction::create("<%i baz.h %>"));

    auto result = c.render(input);

    string expected = "#include \"foo.h\"\r\n"
                      "#include \"bar.h\"\r\n"
                      "#include \"baz.h\"\r\n";

    ASSERT_EQ(expected, result.first);
    ASSERT_TRUE(result.second.empty());
}

TEST(Compiler, SingleStringBlock) {
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("FooBarString"));

    auto result = c.render(input);

    string expected = "ret += \"FooBarString\";";

    ASSERT_TRUE(result.first.empty());
    ASSERT_EQ(expected, result.second);
}

TEST(Compiler, AStringAndACodeBlock)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("FooBarString"));
    input.push_back(Lexer::Instruction::create("<% render(\"partial\"); %>"));

    auto result = c.render(input);

    string expected = "ret += \"FooBarString\";"
                      "render(\"partial\");";

    ASSERT_TRUE(result.first.empty());
    ASSERT_EQ(expected, result.second);
}

TEST(Compiler, MultipleBlocksThatEndUpAsCode)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("FooBarString"));
    input.push_back(Lexer::Instruction::create("<% render(\"partial\"); %>"));
    input.push_back(Lexer::Instruction::create("<%= calculateCRC(); %>"));

    auto result = c.render(input);

    string expected = "ret += \"FooBarString\";"
                      "render(\"partial\");"
                      "ret += calculateCRC();";

    ASSERT_TRUE(result.first.empty());
    ASSERT_EQ(expected, result.second);

}
TEST(Compiler, FullTest)
{
    Compiler c;
    vector<Lexer::Instruction> input;

    input.push_back(Lexer::Instruction::create("<%i foo.h %>"));
    input.push_back(Lexer::Instruction::create("FooBarString"));
    input.push_back(Lexer::Instruction::create("<%i bar.h %>"));
    input.push_back(Lexer::Instruction::create("<% render(\"partial\"); %>"));
    input.push_back(Lexer::Instruction::create("<%i baz.h %>"));
    input.push_back(Lexer::Instruction::create("<%= calculateCRC(); %>"));

    auto result = c.render(input);

    string expected_i = "#include \"foo.h\"\r\n"
                      "#include \"bar.h\"\r\n"
                      "#include \"baz.h\"\r\n";

    string expected_c = "ret += \"FooBarString\";"
                        "render(\"partial\");"
                        "ret += calculateCRC();";

    ASSERT_EQ(expected_i, result.first);
    ASSERT_EQ(expected_c, result.second);

}
