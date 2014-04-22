#include "gtest/gtest.h"
#include "lexer.h"

using namespace ECPP;

TEST(StringInstruction, ContentsShouldBeEqualToWhateverIsPassed) {
  string s = "foo";

  ASSERT_NO_THROW(Lexer::Instruction::createStringInstruction(s));

  Lexer::Instruction si(Lexer::Instruction::createStringInstruction(s));

  ASSERT_EQ(s, si.Contents());
}

TEST(CodeInstruction, ShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<% " + foo + "%>";

  ASSERT_NO_THROW(Lexer::Instruction::createCodeInstruction(s));
  Lexer::Instruction si(Lexer::Instruction::createCodeInstruction(s));

  ASSERT_EQ(foo, si.Contents());
}

TEST(CodeInstruction, ShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::Instruction::createCodeInstruction(s), Lexer::InvalidTokenError);
}

TEST(CodeInstruction, ShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<% " + foo;

  ASSERT_THROW(Lexer::Instruction::createCodeInstruction(s), Lexer::InvalidTokenError);
}

TEST(PrintInstruction, ShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<%=" + foo + "%>";

  ASSERT_NO_THROW(Lexer::Instruction::createPrintInstruction(s));
  Lexer::Instruction i(Lexer::Instruction::createPrintInstruction(s));

  ASSERT_EQ(foo, i.Contents());
}

TEST(PrintInstruction, ShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::Instruction::createPrintInstruction(s), Lexer::InvalidTokenError);
}

TEST(PrintInstruction, ShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<%=" + foo;

  ASSERT_THROW(Lexer::Instruction::createPrintInstruction(s), Lexer::InvalidTokenError);
}

TEST(IncludeInstruction, ShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<%i" + foo + "%>";

  ASSERT_NO_THROW(Lexer::Instruction::createIncludeInstruction(s));
  Lexer::Instruction i(Lexer::Instruction::createIncludeInstruction(s));

  ASSERT_EQ(foo, i.Contents());
}

TEST(IncludeInstruction, ShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::Instruction::createIncludeInstruction(s), Lexer::InvalidTokenError);
}

TEST(IncludeInstruction, ShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<%i" + foo;

  ASSERT_THROW(Lexer::Instruction::createIncludeInstruction(s), Lexer::InvalidTokenError);
}

TEST(LexerCreate, WithAStringToken)
{
  string s = "foo";

  ASSERT_EQ(Lexer::Instruction::Type::STRING, Lexer::Instruction::create(s).Type());
}

TEST(LexerCreate, WithACodeToken)
{
  string s = "<% foo %>";

  ASSERT_EQ(Lexer::Instruction::Type::CODE, Lexer::Instruction::create(s).Type());
}

TEST(LexerCreate, WithAPrintToken)
{
  string s = "<%= foo %>";

  ASSERT_EQ(Lexer::Instruction::Type::PRINT, Lexer::Instruction::create(s).Type());
}

TEST(LexerCreate, WithAnIncludeToken)
{
  string s = "<%i foo %>";

  ASSERT_EQ(Lexer::Instruction::Type::INCLUDE, Lexer::Instruction::create(s).Type());
}