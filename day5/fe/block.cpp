#include "block.h"

#include <string>
#include <numeric>

namespace fe
{
  auto const check_argument_count = [](std::size_t params_count, std::shared_ptr<operation const> const& operation)
  {
    if (params_count != operation->argument_count())
      throw std::invalid_argument("invalid number of parameters for given operation");
    return operation;
  };

  block::block(std::vector<double> params, std::shared_ptr<operation const> const& operation)
    : operation_{check_argument_count(params.size(), operation)}
  {
    params_ = std::move(params);
  }

  double block::operator()(double arg) const
  {
    return (*operation_)(params_, arg);
  }

  bool operator==(block const& lhs, block const& rhs)
  {
    return lhs.params_ == rhs.params_ && *lhs.operation_ == *rhs.operation_;
  }

  bool operator!=(block const& lhs, block const& rhs)
  {
    return !(lhs == rhs);
  }

  std::ostream& operator<<(std::ostream& stream, block const& block)
  {
    using namespace std::string_literals;

    stream << block.operation_->name() << ' ';
    auto params = std::accumulate(block.params_.cbegin(), block.params_.cend(), ""s, 
      [](std::string acc, double v) { return acc + ' ' + std::to_string(v); });
    stream << params << '\n';

    return stream;
  }
}
