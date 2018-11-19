#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../fe/block.h"
#include "../fe/operation_cache.h"

namespace fe::test::unit
{
  TEST_CLASS(block_tests)
  {
    operation_cache cache_ = operation_cache();

  public:
    TEST_METHOD(identity_block_works)
    {
      auto block = fe::block({}, cache_("identity"));
      Assert::AreEqual(2., block(2));
    }

    TEST_METHOD(addition_block_works)
    {
      auto block = fe::block({ 2 }, cache_("addition"));
      Assert::AreEqual(4., block(2));
    }

    TEST_METHOD(multiplication_block_works)
    {
      auto block = fe::block({ 3 }, cache_("multiplication"));
      Assert::AreEqual(6., block(2));
    }

    TEST_METHOD(power_block_works)
    {
      auto block = fe::block({ 3 }, cache_("power"));
      Assert::AreEqual(8., block(2));
    }

    TEST_METHOD(limit_block_works)
    {
      auto block = fe::block({ 0, 2 }, cache_("limit"));
      Assert::AreEqual(0., block(-1.));
      Assert::AreEqual(0., block(0.));
      Assert::AreEqual(1., block(1.));
      Assert::AreEqual(2., block(2.));
      Assert::AreEqual(2., block(3.));
    }

    TEST_METHOD(condition_block_works)
    {
      auto block = fe::block({ 2 }, cache_("condition"));
      Assert::AreEqual(-1., block(1.));
      Assert::AreEqual(0., block(2.));
      Assert::AreEqual(1., block(3.));
    }
  };
}