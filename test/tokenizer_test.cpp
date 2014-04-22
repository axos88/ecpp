#include "gtest/gtest.h"
#include "tokenizer.h"


TEST(Tokenizer, SimpleString) {

  string s = "foo";
  vector<string> v;

  v.push_back(s);


  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, SingleCodeBlock) {

  string s = "<%= foo() %>";

  vector<string> v;

  v.push_back(s);


  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, CodeBlockInTheMiddle) {

  string s = "foo <%= bar() %>baz";

  vector<string> v;

  v.push_back("foo ");
  v.push_back("<%= bar() %>");
  v.push_back("baz");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, CodeBlockSurroundedByWhitespace) {

  string s = "\n\t <%= bar() %>  ";

  vector<string> v;

  v.push_back("\n\t ");
  v.push_back("<%= bar() %>");
  v.push_back("  ");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, QuotedEnclosingCodeBlock) {

  string s = "foo<%= bar(\"%>\") %>  ";

  vector<string> v;

  v.push_back("foo");
  v.push_back("<%= bar(\"%>\") %>");
  v.push_back("  ");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, EscapedOpenBlock) {
  string s = "foo <%% bar() <% blah() %>";

  vector<string> v;

  v.push_back("foo <% bar() ");
  v.push_back("<% blah() %>");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, EscapedCloseBlock) {
  string s = "foo <% bar() %%> blah(); %>";

  vector<string> v;

  v.push_back("foo ");
  v.push_back("<% bar() %> blah(); %>");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}



TEST(Tokenizer, WhenStartingWithCodeBlock) {
  string s = "<% foo() %> bar";

  vector<string> v;

  v.push_back("<% foo() %>");
  v.push_back(" bar");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, WhenEndingWithCodeBlock) {
  string s = "<% foo() %> bar <% baz   %>";

  vector<string> v;

  v.push_back("<% foo() %>");
  v.push_back(" bar ");
  v.push_back("<% baz   %>");

  EXPECT_EQ(v, ECPP::Tokenizer::tokenize(s));
}

TEST(Tokenizer, DISABLE_ShouldIssueWarningWhenStartingWithWhiteSpace) {

}

TEST(Tokenizer, DISABLE_ShouldIssueWarningWhenEndingWithWhiteSpace) {

}
