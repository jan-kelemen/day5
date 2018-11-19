#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../fe/operation_cache.h"

namespace fe::test::unit
{
  TEST_CLASS(operation_cache_test)
  {
  public:
    TEST_METHOD(operation_cache_contains_at_least_identity_operation)
    {
      auto cache = operation_cache();
      auto const&[begin, end] = cache.names();
      auto identity_iterator = std::find(begin, end, "identity");

      Assert::IsTrue(identity_iterator != end);
    }
  };
}