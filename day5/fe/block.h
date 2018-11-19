#pragma once

#include "operation.h"
#include <memory>

namespace fe
{
  class block
  {
  public:
    block() = default;
    block(std::vector<double> params, std::shared_ptr<operation const> const& operation);
    block(block const&) = default;
    block(block&&) = default;

    double operator()(double arg) const;

    block& operator=(block const&) = default;
    block& operator=(block&&) = default;

    ~block() = default;
  private:
    std::vector<double> params_;
    std::shared_ptr<operation const> operation_;

    friend bool operator==(block const&, block const&);
  };

  bool operator==(block const& lhs, block const& rhs);
  bool operator!=(block const& lhs, block const& rhs);
}
