// Copyright 2014, Vandra Akos
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <limits.h>
#include "gtest/gtest.h"
#include "ecpp.h"


TEST(Tokenizer, SimpleString) {

  string s = "foo";
  vector<string> v;

  v.push_back(s);


  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, SingleCodeBlock) {

  string s = "<%= foo() %>";

  vector<string> v;

  v.push_back(s);


  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, CodeBlockInTheMiddle) {

  string s = "foo <%= bar() %>baz";

  vector<string> v;

  v.push_back("foo ");
  v.push_back("<%= bar() %>");
  v.push_back("baz");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, CodeBlockSurroundedByWhitespace) {

  string s = "\n\t <%= bar() %>  ";

  vector<string> v;

  v.push_back("\n\t ");
  v.push_back("<%= bar() %>");
  v.push_back("  ");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, QuotedEnclosingCodeBlock) {

  string s = "\n\t <%= bar(\"%>\") %>  ";

  vector<string> v;

  v.push_back("\n\t ");
  v.push_back("<%= bar(\"%>\") %>");
  v.push_back("  ");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, EscapedOpenBlock) {
  string s = "foo <\\% bar() %>";

  vector<string> v;

  v.push_back("foo <\% bar() %>");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, WhenStartingWithCodeBlock) {
  string s = "<% foo() %> bar";

  vector<string> v;

  v.push_back("<% foo %>");
  v.push_back(" bar");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, WhenEndingWithCodeBlock) {
  string s = "<% foo() %> bar <% baz   %>";

  vector<string> v;

  v.push_back("<% foo %>");
  v.push_back(" bar ");
  v.push_back("<% baz   %>");

  EXPECT_EQ(v, ECPP::tokenize(s));
}

TEST(Tokenizer, DISABLE_ShouldIssueWarningWhenStartingWithWhiteSpace) {

}

TEST(Tokenizer, DISABLE_ShouldIssueWarningWhenEndingWithWhiteSpace) {

}
