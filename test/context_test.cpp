#include "gtest/gtest.h"
#include "context.h"

using namespace ECPP;

TEST(RenderContext, RetrieveCorrectType) {
  RenderContext rc;

  int i = 5;

  rc.export_by_move<int>("val", &i);
  int j = rc.import<int>("val");

  ASSERT_EQ(i, j);
}

TEST(RenderContext, RetrieveUnsetValue) {
  RenderContext rc;

  ASSERT_THROW(rc.import<int>("val"), RenderContext::KeyNotFoundError);
}

TEST(RenderContext, OverwriteAlreadySetValue) {
  RenderContext rc;

  int i = 5;
  int j = 6;

  ASSERT_NO_THROW(rc.export_by_move<int>("val", &i));
  ASSERT_NO_THROW(rc.export_by_move<int>("val", &j));

  int k = rc.import<int>("val");

  ASSERT_EQ(j, k);
}

TEST(RenderContext, RetrievingWrongType) {
  RenderContext rc;

  int i = 5;

  ASSERT_NO_THROW(rc.export_by_move<int>("val", &i));

  ASSERT_THROW(rc.import<long>("val"), RenderContext::InvalidTypeError);
}