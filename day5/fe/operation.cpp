#include "operation.h"

#include <algorithm>

#include "operation_factory.h"

namespace fe
{
  std::string const& operation::id() const { return id_; }
  std::size_t operation::argument_count() const { return argument_count_; }
  std::string const & operation::name() const { return name_; }

  operation::operation(std::string id, std::size_t argument_count, std::string name)
    : id_{std::move(id)}
    , argument_count_{std::move(argument_count)}
    , name_{std::move(name)}
  {
    ;
  }

  class identity : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{BB366C59-D581-449D-B5FD-68EE715CF5AA}";

    identity() : operation(registration_id, 0, "identity") {}

    identity(identity const&) = default;
    identity(identity&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override { return arg; }

    identity& operator=(identity const&) = default;
    identity& operator=(identity&&) = default;

    virtual ~identity() = default;
  };
  std::size_t identity::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<identity>(); });

  class addition : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{5A5AFFA2-7009-4598-ADC2-EC89C5DDB59C}";

    addition() : operation(registration_id, 1, "addition") {}

    addition(addition const&) = default;
    addition(addition&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override { return params[0] + arg; }

    addition& operator=(addition const&) = default;
    addition& operator=(addition&&) = default;

    virtual ~addition() = default;
  };
  std::size_t addition::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<addition>(); });

  class multiplication : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{6CF83378-A6FC-4608-9085-65957EFBE6B9}";

    multiplication() : operation(registration_id, 1, "multiplication") {}

    multiplication(multiplication const&) = default;
    multiplication(multiplication&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override { return params[0] * arg; }

    multiplication& operator=(multiplication const&) = default;
    multiplication& operator=(multiplication&&) = default;

    virtual ~multiplication() = default;
  };
  std::size_t multiplication::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<multiplication>(); });

  class power : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{8F7094D7-EB75-40F1-A3AD-6F9C4989FAEB}";

    power() : operation(registration_id, 1, "power") {}

    power(power const&) = default;
    power(power&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override { return std::pow(arg, params[0]); }

    power& operator=(power const&) = default;
    power& operator=(power&&) = default;

    virtual ~power() = default;
  };
  std::size_t power::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<power>(); });

  class limit : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{A72FF701-99E2-47AF-B8E2-1ACEAD5A89A3}";

    limit() : operation(registration_id, 2, "limit") {}

    limit(limit const&) = default;
    limit(limit&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override { return std::clamp(arg, params[0], params[1]); }

    limit& operator=(limit const&) = default;
    limit& operator=(limit&&) = default;

    virtual ~limit() = default;
  };
  std::size_t limit::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<limit>(); });

  class condition : public operation
  {
    static std::size_t factory_id;
  public:
    constexpr static auto registration_id = "{1D474882-DB3A-4A07-BFC1-41C4AB7BB48A}";

    condition() : operation(registration_id, 1, "condition") {}

    condition(condition const&) = default;
    condition(condition&&) = default;

    double operator()(std::vector<double> const& params, double arg) const override
    {
      if (arg < params[0]) return -1;
      if (arg > params[0]) return 1;
      return 0;
    }

    condition& operator=(condition const&) = default;
    condition& operator=(condition&&) = default;

    virtual ~condition() = default;
  };
  std::size_t condition::factory_id = operation_factory.register_creator(registration_id, []() { return std::make_unique<condition>(); });
}



