#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../fe/operation_cache.h"
#include "../fe/block_sequence.h"

namespace fe::test::unit
{
  TEST_CLASS(block_sequence_tests)
  {
    operation_cache cache_ = operation_cache();

  public:
    TEST_METHOD(block_sequence_is_empty_by_default)
    {
      auto sequence = block_sequence();
      Assert::AreEqual(std::size_t{ 0 }, sequence.size());
    }

    TEST_METHOD(block_sequence_add_new_block_to_end_works)
    {
      auto sequence = block_sequence();
      sequence.add(block({}, cache_("identity")));
      Assert::AreEqual(std::size_t{ 1 }, sequence.size());
    }

    TEST_METHOD(block_sequence_remove_works)
    {
      auto sequence = block_sequence();
      sequence.add(block({}, cache_("identity")));
      Assert::AreEqual(std::size_t{ 1 }, sequence.size());
      sequence.remove(0);
      Assert::AreEqual(std::size_t{ 0 }, sequence.size());
    }

    TEST_METHOD(block_sequence_move_to_beginning_works)
    {
      auto sequence = block_sequence();
      sequence.add(block({}, cache_("identity")));
      sequence.add(block({ 2 }, cache_("addition")));
      sequence.add(block({ 3 }, cache_("multiplication")));
      Assert::AreEqual(std::size_t{ 3 }, sequence.size());

      Assert::AreEqual(9., sequence(1));
      sequence.move_to_beginning(2);
      Assert::AreEqual(5., sequence(1));
    }
  };
}