#include "gtest/gtest.h"
#include "context.h"

using namespace ECPP;

TEST(RenderContext, RetrieveCorrectType) {
  RenderContext rc;

  int i = 5;

  ECPP_EXPORT(rc, "val", int, i);
  ECPP_IMPORT(rc, "val", int, j);

  ASSERT_EQ(i, j);
}

TEST(RenderContext, RetrieveUnsetValue) {
  RenderContext rc;

  auto func = [&]() {
    ECPP_IMPORT(rc, "val", int, j)

    return j;
  };

  ASSERT_THROW(func(), RenderContext::KeyNotFoundError);
}

TEST(RenderContext, OverwriteAlreadySetValue) {
  RenderContext rc;

  int i = 5;
  int j = 6;

  auto func = [&](int& x) {
    ECPP_EXPORT(rc, "val", int, x);
  };

  ASSERT_NO_THROW(func(i));
  ASSERT_NO_THROW(func(j));

  ECPP_IMPORT(rc, "val", int, k);

  ASSERT_EQ(j, k);
}

TEST(RenderContext, RetrievingWrongType) {
  RenderContext rc;

  int i = 5;

  ECPP_EXPORT(rc, "val", int, i);

  auto func = [&]() {
    ECPP_IMPORT(rc, "val", long, j);
    return j;
  };

  ASSERT_THROW(func(), RenderContext::InvalidTypeError);
}