#pragma once

#include <vector>

namespace fe
{
  class operation
  {
  public:
    operation() = delete;
    operation(operation const&) = default;
    operation(operation&&) = default;

    std::string const& id() const;
    std::size_t argument_count() const;
    std::string const& name() const;
    virtual double operator()(std::vector<double> const& params, double arg) const = 0;

    operation& operator=(operation const&) = default;
    operation& operator=(operation&&) = default;

    virtual ~operation() = default;
  protected:
    operation(std::string id, std::size_t argument_count, std::string name);
  private:
    std::string id_{};
    std::size_t argument_count_{};
    std::string name_{};
  };

  bool operator==(operation const& lhs, operation const& rhs);
  bool operator!=(operation const& lhs, operation const& rhs);
}
