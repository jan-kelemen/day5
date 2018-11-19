#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../fe/operation_factory.h"

namespace fe::test::unit
{
  TEST_CLASS(operation_factory_test)
  {
  public:
    TEST_METHOD(double_registration_throws_invalid_argument)
    {
      auto registration = []() { operation_factory.register_creator("{06E15A4B-9E3D-48A0-A836-29C507ED9D71}", [] { return nullptr; }); };

      //execute first registration
      registration();

      //expect exception on second registration
      Assert::ExpectException<std::invalid_argument>(registration);
    }

    TEST_METHOD(unregistered_id_throws_out_of_range)
    {
      auto get_registered = []() { return operation_factory("{5EEEAA72-0F17-4630-81C8-D52084BB9483}"); };

      Assert::ExpectException<std::out_of_range>(get_registered);
    }
  };
}