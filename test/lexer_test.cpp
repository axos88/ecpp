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

using namespace ECPP;

TEST(StringInstruction, ContentsShouldBeEqualToWhateverIsPassed) {
  string s = "foo";

  ASSERT_NO_THROW(Lexer::StringInstruction si(s));

  Lexer::StringInstruction si(s);

  ASSERT_EQ(s, si.Contents());
}

TEST(CodeInstruction, ContentsShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<% " + foo + "%>";

  ASSERT_NO_THROW(Lexer::CodeInstruction si(s));
  Lexer::CodeInstruction si(s);

  ASSERT_EQ(foo, si.Contents());
}

TEST(CodeInstruction, ContentsShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::CodeInstruction si(s), Lexer::InvalidTokenError);
}

TEST(CodeInstruction, ContentsShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<% " + foo;

  ASSERT_THROW(Lexer::CodeInstruction si(s), Lexer::InvalidTokenError);
}



TEST(PrintInstruction, ContentsShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<%=" + foo + "%>";

  ASSERT_NO_THROW(Lexer::PrintInstruction i(s));
  Lexer::PrintInstruction i(s);

  ASSERT_EQ(foo, i.Contents());
}

TEST(PrintInstruction, ContentsShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::PrintInstruction i(s), Lexer::InvalidTokenError);
}

TEST(PrintInstruction, ContentsShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<%=" + foo;

  ASSERT_THROW(Lexer::PrintInstruction i(s), Lexer::InvalidTokenError);
}



TEST(IncludeInstruction, ContentsShouldRemoveStartAndEndTags) {
  string foo = "foo";
  string s = "<%i" + foo + "%>";

  ASSERT_NO_THROW(Lexer::IncludeInstruction i(s));
  Lexer::IncludeInstruction i(s);

  ASSERT_EQ(foo, i.Contents());
}

TEST(IncludeInstruction, ContentsShouldThrowIfStartTagIsMissing) {
  string foo = "foo";
  string s = foo + "%>";

  ASSERT_THROW(Lexer::IncludeInstruction i(s), Lexer::InvalidTokenError);
}

TEST(IncludeInstruction, ContentsShouldThrowIfEndTagIsMissing) {
  string foo = "foo";
  string s = "<%i" + foo;

  ASSERT_THROW(Lexer::IncludeInstruction i(s), Lexer::InvalidTokenError);
}